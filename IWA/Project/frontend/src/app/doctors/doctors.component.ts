import { Component } from '@angular/core';
import { Doctor } from '../models/doctor.model';
import { MatTableDataSource } from '@angular/material/table';
import { MatSort } from '@angular/material/sort';
import { ViewChild } from '@angular/core';
import { Router } from '@angular/router';
import { UserService } from '../services/user.service';
import { TokenStorageService } from '../auth/token-storage.service';

@Component({
  selector: 'app-doctors',
  templateUrl: './doctors.component.html',
  styleUrl: './doctors.component.css'
})
export class DoctorsComponent {
  username?: string;
  roles: string[] = [];
  authority: string = '';

  doctors: Doctor[] = [];
  dataSource = new MatTableDataSource<Doctor>();
  displayedColumns: string[] = ['firstName', 'lastName', 'specialization'];
  @ViewChild(MatSort, { static: true }) sort!: MatSort;

  constructor(private userService: UserService, private router: Router,
              private tokenStorage: TokenStorageService,
  ) {}

  ngOnInit(): void {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();
    this.getDoctors();
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }

  getDoctors() {
    this.userService.getDoctors().subscribe(doctors => {
      this.doctors = doctors;
      this.dataSource.data = this.doctors;
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
    this.router.navigate(['/user-panel/doctor-detail', row.id]);
  }
}
