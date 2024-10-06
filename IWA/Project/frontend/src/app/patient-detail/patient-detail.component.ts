import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Route, Router } from '@angular/router';
import { Patient } from '../models/patient.model';
import { TokenStorageService } from '../auth/token-storage.service';
import { FormGroup, FormControl } from '@angular/forms';
import { UserService } from '../services/user.service';
@Component({
  selector: 'app-patient-detail',
  templateUrl: './patient-detail.component.html',
  styleUrl: './patient-detail.component.css'
})
export class PatientDetailComponent {
  username?: string;
  roles: string[] = [];
  authority: string = '';
  patientId?: string | null;
  patient?: Patient;
  isEdit: boolean = false;

  patientForm!: FormGroup;

  constructor(private route: ActivatedRoute, private tokenStorage: TokenStorageService,
              private userService: UserService, private router: Router,
  ) {}

  ngOnInit() {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();

    this.patientId = this.route.snapshot.params['id'];
    this.isEdit = isNaN(Number(this.patientId));

    this.patientForm = new FormGroup({
      firstName: new FormControl(''),
      lastName: new FormControl(''),
      medicalHistory: new FormControl(''),
    });

    if (this.authority === 'user') {
      this.router.navigate(['/user-panel/patients']);
    } else if (this.authority === 'doctor') {
      this.getPatient();
    } else if (this.authority === 'admin') {
      this.getPatient();
    }
  }

  getPatient() {
    this.patientId = this.route.snapshot.params['id'];
    this.userService.getPatientByID(Number(this.patientId)).subscribe(patient => {
      this.patient = patient;
      this.loadDoctorDetails();
    });
  }

  loadDoctorDetails() {
    if (this.patient) {
      this.patientForm.setValue({
        firstName: this.patient.firstName,
        lastName: this.patient.lastName,
        medicalHistory: this.patient.medicalHistory,
      });
    }
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }

  onSubmit() {

  }

  save() {
    if (this.patient) {
      const firstName = this.patientForm.get('firstName')?.value;
      const lastName = this.patientForm.get('lastName')?.value;
      const medicalHistory = this.patientForm.get('medicalHistory')?.value;

      if (!firstName || !lastName) {
        console.log("Empty name fields");
        return;
      }

      const patient = new Patient(
        this.patient.id,
        this.patient.user,
        firstName,
        lastName,
        medicalHistory
      );

      console.log(patient);

      this.userService.updatePatient(patient, this.patient.id).subscribe({
        next: (updated) => {
        console.log("Patient updated:", updated);
        this.patient = updated;
        alert("Doctor updated");
      },
        error: (error) => console.error('Failed to update patient:', error.message)
      });

    }
  }
}
