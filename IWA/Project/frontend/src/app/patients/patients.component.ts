import { Component, OnInit } from '@angular/core';
import { Patient } from '../models/patient.model';
import { MatTableDataSource } from '@angular/material/table';
import { MatSort } from '@angular/material/sort';
import { ViewChild } from '@angular/core';
import { Router } from '@angular/router';
import { UserService } from '../services/user.service';
import { TokenStorageService } from '../auth/token-storage.service';


@Component({
  selector: 'app-patients',
  templateUrl: './patients.component.html',
  styleUrl: './patients.component.css'
})
export class PatientsComponent implements OnInit {
  username?: string;
  roles: string[] = [];
  authority: string = '';

  patients: Patient[] = [];
  dataSource = new MatTableDataSource<Patient>();
  displayedColumns: string[] = ['firstName', 'lastName', 'medicalHistory'];
  @ViewChild(MatSort, { static: true }) sort!: MatSort;

  constructor(private userService: UserService, private router: Router,
              private tokenStorage: TokenStorageService,
  ) {}

  ngOnInit(): void {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();
    this.getPatients();
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }

  getPatients() {
    this.userService.getPatients().subscribe(patients => {
      this.patients = patients;
      this.dataSource.data = this.patients;
    });
  }

  ngAfterViewInit() {
    this.dataSource.sort = this.sort;
  }


  applyFilter(event: Event): void {
    const filterValue = (event.target as HTMLInputElement).value;
    this.dataSource.filter = filterValue.trim().toLowerCase();
  }

  onRowClicked(row: any) {
    this.router.navigate(['/user-panel/patient-detail', row.id]);
  }
}
