import { Component, OnInit } from '@angular/core';
import { ActivatedRoute, Route, Router } from '@angular/router';
import { Doctor } from '../models/doctor.model';
import { TokenStorageService } from '../auth/token-storage.service';
import { FormGroup, FormControl } from '@angular/forms';
import { UserService } from '../services/user.service';

@Component({
  selector: 'app-doctor-detail',
  templateUrl: './doctor-detail.component.html',
  styleUrl: './doctor-detail.component.css'
})
export class DoctorDetailComponent {
  username?: string;
  roles: string[] = [];
  authority: string = '';
  doctorId?: string | null;
  doctor?: Doctor;
  isEdit: boolean = false;

  doctorForm!: FormGroup;

  constructor(private route: ActivatedRoute, private tokenStorage: TokenStorageService,
              private userService: UserService, private router: Router,
  ) {}

  ngOnInit() {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();

    this.doctorId = this.route.snapshot.params['id'];
    this.isEdit = isNaN(Number(this.doctorId));

    this.doctorForm = new FormGroup({
      firstName: new FormControl(''),
      lastName: new FormControl(''),
      specialization: new FormControl(''),
    });

    if (this.authority === 'user') {
      this.router.navigate(['/user-panel/doctors']);
    } else if (this.authority === 'doctor') {
      this.router.navigate(['/user-panel/doctors']);
    } else if (this.authority === 'admin') {
      this.getDoctor();
    }
  }

  getDoctor() {
    this.doctorId = this.route.snapshot.params['id'];
    this.userService.getDoctorByID(Number(this.doctorId)).subscribe(doctor => {
      this.doctor = doctor;
      this.loadDoctorDetails();
    });
  }

  loadDoctorDetails() {
    if (this.doctor) {
      this.doctorForm.setValue({
        firstName: this.doctor.firstName,
        lastName: this.doctor.lastName,
        specialization: this.doctor.specialization,
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
    if (this.doctor) {
      const firstName = this.doctorForm.get('firstName')?.value;
      const lastName = this.doctorForm.get('lastName')?.value;
      const specialization = this.doctorForm.get('specialization')?.value;

      if (!firstName || !lastName) {
        console.log("Empty name fields");
        return;
      }

      const doctor = new Doctor(
        this.doctor.id,
        this.doctor.user,
        firstName,
        lastName,
        specialization
      );

      console.log(doctor);

      this.userService.updateDoctor(doctor, this.doctor.id).subscribe({
        next: (updated) => {
        console.log("Doctor updated:", updated);
        this.doctor = updated;
        alert("Doctor updated");
      },
        error: (error) => console.error('Failed to update patient:', error.message)
      });

    }
  }
}
