import { Component, OnInit } from '@angular/core';
import { TokenStorageService } from '../auth/token-storage.service';
import { Patient } from '../models/patient.model';
import { Doctor } from '../models/doctor.model';
import { Router } from '@angular/router';
import { UserService } from '../services/user.service';

@Component({
  selector: 'app-profile',
  templateUrl: './profile.component.html',
  styleUrl: './profile.component.css'
})
export class ProfileComponent implements OnInit {
  username: string = '';
  roles: string[] = [];
  authority: string = '';
  patient?: Patient;
  doctor?: Doctor;
  
  constructor(private tokenStorage: TokenStorageService, private router: Router,
              private userService: UserService
  ) {}

  getPatient() {
    this.username = this.tokenStorage.getUsername();
    this.userService.getPatient(this.username).subscribe(patient => this.patient = patient);
  }

  getDoctor() {
    this.username = this.tokenStorage.getUsername();
    this.userService.getDoctor(this.username).subscribe(doctor => this.doctor = doctor);
  }

  ngOnInit() {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();

    if (this.authority === 'user') {
      this.getPatient();
    } else if (this.authority === 'doctor') {
      this.getDoctor();
    } else if (this.authority === 'admin') {
      this.router.navigate(['/user-panel']);
    }
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }
}
