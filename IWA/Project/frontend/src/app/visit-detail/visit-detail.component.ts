import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Visit } from '../models/visit.model';
import { Doctor } from '../models/doctor.model';
import { Patient } from '../models/patient.model';
import { TokenStorageService } from '../auth/token-storage.service';
import { VisitService } from '../services/visit.service';
import { FormGroup, FormControl } from '@angular/forms';
import { UserService } from '../services/user.service';
import { Prescription } from '../models/prescription.model';

@Component({
  selector: 'app-visit-detail',
  templateUrl: './visit-detail.component.html',
  styleUrl: './visit-detail.component.css'
})
export class VisitDetailComponent implements OnInit {
  username?: string;
  roles: string[] = [];
  authority: string = '';
  visitId?: string | null;
  visit?: Visit;
  isEdit: boolean = false;

  visitForm!: FormGroup;
  prescriptionForm!: FormGroup;

  doctors: Doctor[] = [];
  patients: Patient[] = [];
  times: string[] = [];

  constructor(private route: ActivatedRoute, private tokenStorage: TokenStorageService,
              private visitService: VisitService, private userService: UserService,
  ) {}

  getPatientVisit() {
    this.username = this.tokenStorage.getUsername();
    this.visitId = this.route.snapshot.paramMap.get('id');
    this.visitService.getPatientVisit(this.username, Number(this.visitId)).subscribe(visit => {
      this.visit = visit;
    });
  }

  getDoctorVisit() {
    this.username = this.tokenStorage.getUsername();
    this.visitId = this.route.snapshot.paramMap.get('id');
    this.visitService.getDoctorVisit(this.username, Number(this.visitId)).subscribe(visit => {
      this.visit = visit;
      this.loadVisitDetails();
    });
  }

  getVisit() {
    this.visitId = this.route.snapshot.paramMap.get('id');
    this.visitService.getVisit(Number(this.visitId)).subscribe(visit => {
      this.visit = visit;
      this.loadVisitDetails();
    });
  }

  getPatients() {
    this.userService.getPatients().subscribe(patients => this.patients = patients);
  }

  getDoctors() {
    this.userService.getDoctors().subscribe(doctors => this.doctors = doctors);
  }

  ngOnInit() {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();

    this.visitId = this.route.snapshot.params['id'];
    this.isEdit = isNaN(Number(this.visitId));

    this.visitForm = new FormGroup({
      doctor: new FormControl(''),
      patient: new FormControl(''),
      visitDate: new FormControl(''),
      time: new FormControl(''),
      notes: new FormControl(''),
      isCanceled: new FormControl('no')
    });

    this.prescriptionForm = new FormGroup({
      medication: new FormControl(''),
      description: new FormControl(''),
    });

    this.setUpTimeOptions();

    if (this.authority === 'user') {
      this.getPatientVisit();
    } else if (this.authority === 'doctor') {
      this.getPatients();
      this.getDoctors();
      this.getDoctorVisit();
    } else if (this.authority === 'admin') {
      this.getPatients();
      this.getDoctors();
      this.getVisit();
    }
  }

  setUpTimeOptions() {
    this.times = [];
    for (let hour = 7; hour <= 17; hour++) {
      if (hour !== 17) {
        this.times.push(`${hour < 10 ? '0' + hour : hour}:00`);
        this.times.push(`${hour < 10 ? '0' + hour : hour}:30`);
      } else {
        this.times.push(`${hour}:00`);
      }
    }
    this.visitForm.get('time')?.setValue(this.times[0]);
  }

  private combineDateTime(date: Date, time: string): Date {
    const timeParts = time.split(':');
    const dateCopy = new Date(date);
    dateCopy.setHours(parseInt(timeParts[0]), parseInt(timeParts[1]));
    return dateCopy;
  }

  loadVisitDetails() {
    if (this.visit) {
      const visitDate = new Date(this.visit.visitDate);
      this.visitForm.setValue({
        doctor: this.visit.doctor.id,
        patient: this.visit.patient.id,
        visitDate: visitDate,
        time: visitDate.toTimeString().substring(0, 5),
        notes: this.visit.notes,
        isCanceled: this.visit.isCanceled ? 'yes' : 'no',
      });

      console.log(this.visit.prescription);

      if (this.visit.prescription) {
        this.prescriptionForm.setValue({
          medication: this.visit.prescription.medication,
          description: this.visit.prescription.description,
        });
      }
    }
    
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }

  onSubmit() {
    const doctorId = this.visitForm.get('doctor')?.value;
    const patientId = this.visitForm.get('patient')?.value;
  
    const doctor = this.doctors.find(d => d.id === doctorId);
    const patient = this.patients.find(p => p.id === patientId);

    if (!doctor || !patient) {
      console.error('Doctor or patient not found');
      return;
    }

    const prescription = new Prescription(
      0,
      doctor,
      patient,
      this.prescriptionForm.get('medication')?.value,
      this.prescriptionForm.get('description')?.value,
    );

    const visitDate = this.combineDateTime(this.visitForm.get('visitDate')?.value, this.visitForm.get('time')?.value);
    const isCanceled = this.visitForm.get('isCanceled')?.value === 'yes';
  
    const addedVisit = new Visit(
      0,
      doctor,
      patient,
      prescription,
      visitDate,
      this.visitForm.get('notes')?.value,
      isCanceled,
    );

    console.log(addedVisit);
    
    this.visitService.addVisit(addedVisit).subscribe({
      next: (added) => {
        console.log("Visit added:", added);
        this.visit = added;
        alert("Visit added");
      },
      error: (error) => console.error('Failed to add visit:', error.message)
    });

  }

  save() {
    if (this.visit) {
      const doctorId = this.visitForm.get('doctor')?.value;
      const patientId = this.visitForm.get('patient')?.value;
    
      const doctor = this.doctors.find(d => d.id === doctorId);
      const patient = this.patients.find(p => p.id === patientId);
    
      if (!doctor || !patient) {
        console.error('Doctor or patient not found');
        return;
      }
    
      const prescription = new Prescription(
        this.visit.prescription.id,
        doctor,
        patient,
        this.prescriptionForm.get('medication')?.value,
        this.prescriptionForm.get('description')?.value,
      );
    
      const visitDate = this.combineDateTime(this.visitForm.get('visitDate')?.value, this.visitForm.get('time')?.value);
      const isCanceled = this.visitForm.get('isCanceled')?.value === 'yes';
  
      const updatedVisit = new Visit(
        this.visit?.id,
        doctor,
        patient,
        prescription,
        visitDate,
        this.visitForm.get('notes')?.value,
        isCanceled,
      );

      console.log(updatedVisit);
    
      this.visitService.updateVisit(updatedVisit, this.visit?.id).subscribe({
        next: (updated) => {
          console.log("Visit updated:", updated);
          this.visit = updated;
          alert("Visit updated");
        },
        error: (error) => console.error('Failed to update visit:', error.message)
      });
    }
  }

  isUpcomingAndActive(): boolean {
    if (!this.visit) {
      return false;
    }

    const now = new Date();
    const visitDate = new Date(this.visit.visitDate);

    return visitDate > now && !this.visit.isCanceled;
  }

  cancel() {
    if (this.visit && this.username) {
      this.visitService.cancelVisit(this.username, this.visit.id).subscribe({
        next: (canceled) => {
          console.log("Visit canceled:", canceled);
          this.visit = canceled;
          alert("Visit canceled");
        },
        error: (error) => console.error('Failed to cancel visit:', error.message)
      });
    }
  }
}
