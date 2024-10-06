import { Component, OnInit } from '@angular/core';
import { Patient } from '../models/patient.model';
import { Doctor } from '../models/doctor.model';
import { UserService } from '../services/user.service';
import { TokenStorageService } from '../auth/token-storage.service';

@Component({
  selector: 'app-user-panel',
  templateUrl: './user-panel.component.html',
  styleUrl: './user-panel.component.css'
})
export class UserPanelComponent implements OnInit {
  username?: string;
  user?: Patient | Doctor;
  roles: string[] = [];
  authority: string = '';

  constructor(private userService: UserService, private tokenStorage: TokenStorageService) {}

  getPatient() {
    this.username = this.tokenStorage.getUsername();
    this.userService.getPatient(this.username).subscribe(user => this.user = user);
  }

  getDoctor() {
    this.username = this.tokenStorage.getUsername();
    this.userService.getDoctor(this.username).subscribe(user => this.user = user);
  }

  ngOnInit(): void {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();

    if (this.authority === 'user') {
      this.getPatient();
    } else if (this.authority === 'doctor') {
      this.getDoctor();
    } else if (this.authority === 'admin') {
      this.username = this.tokenStorage.getUsername();
    }
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }

  logout() {
    this.tokenStorage.signOut();
    window.location.reload();
  }
}
