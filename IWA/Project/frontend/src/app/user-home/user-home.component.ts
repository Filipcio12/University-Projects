import { Component } from '@angular/core';
import { Patient } from '../models/patient.model';
import { Doctor } from '../models/doctor.model';
import { Visit } from '../models/visit.model';
import { UserService } from '../services/user.service';
import { TokenStorageService } from '../auth/token-storage.service';
import { AdminService } from '../services/admin.service';
import { MatTableDataSource } from '@angular/material/table';
import { MatSort } from '@angular/material/sort';
import { ViewChild } from '@angular/core';
import { VisitService } from '../services/visit.service';
import { Router } from '@angular/router';

@Component({
  selector: 'app-user-home',
  templateUrl: './user-home.component.html',
  styleUrl: './user-home.component.css'
})
export class UserHomeComponent {
  username?: string;
  user?: Patient | Doctor;
  roles: string[] = [];
  authority: string = '';
  status: any = {};
  visits: Visit[] = [];
  dataSource = new MatTableDataSource<Visit>();
  displayedColumns: string[] = ['doctor', 'patient', 'prescription', 'date', 'time', 'notes', 'isCanceled'];
  @ViewChild(MatSort, { static: true }) sort!: MatSort;

  constructor(private userService: UserService, private tokenStorage: TokenStorageService,
              private adminService: AdminService, private visitService: VisitService,
              private router: Router,
  ) {}

  getPatient() {
    this.username = this.tokenStorage.getUsername();
    this.userService.getPatient(this.username).subscribe(user => this.user = user);
  }

  getDoctor() {
    this.username = this.tokenStorage.getUsername();
    this.userService.getDoctor(this.username).subscribe(user => this.user = user);
  }

  transformVisit(visit: Visit) {
    const visitDate = new Date(visit.visitDate);
    return {
      ...visit,
      doctorName: `${visit.doctor?.firstName} ${visit.doctor?.lastName}`,
      patientName: `${visit.patient?.firstName} ${visit.patient?.lastName}`,
      medication: visit.prescription.medication,
      date: visitDate,
      time: visitDate instanceof Date ? visitDate.toTimeString().substring(0, 5) : ""
    };
  }

  getUpcomingPatientVisits() {
    this.username = this.tokenStorage.getUsername();
    this.visitService.getUpcomingPatientVisits(this.username).subscribe(visits => {
      this.visits = visits.map(visit => this.transformVisit(visit));
      this.dataSource.data = this.visits;
    });
  }

  getUpcomingDoctorVisits() {
    this.username = this.tokenStorage.getUsername();
    this.visitService.getUpcomingDoctorVisits(this.username).subscribe(visits => {
      this.visits = visits.map(visit => this.transformVisit(visit));
      this.dataSource.data = this.visits;
    });
  }

  getAllUpcomingVisits() {
    this.visitService.getAllUpcomingVisits().subscribe(visits => {
      this.visits = visits.map(visit => this.transformVisit(visit));
      this.dataSource.data = this.visits;
    });
  }

  ngOnInit(): void {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();

    if (this.authority === 'user') {
      this.getPatient();
      this.getUpcomingPatientVisits();
    } else if (this.authority === 'doctor') {
      this.getDoctor();
      this.getUpcomingDoctorVisits();
    } else if (this.authority === 'admin') {
      this.adminService.getStatus().subscribe(status => this.status = status);
      this.getAllUpcomingVisits();
    }
  }

  ngAfterViewInit() {
    this.dataSource.sort = this.sort;
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }

  onRowClicked(row: any) {
    this.router.navigate(['/user-panel/visit-detail', row.id]);
  }

  checkAvailability(visit: Visit): string {
    if (visit.isCanceled) {
      return 'event_busy';
    }

    const visitDate = new Date(visit.visitDate);
    const now = new Date();

    if (visitDate > now) {
      return 'event';
    }

    return 'event_available';
  }

  getAvailabilityTooltip(visit: Visit): string {
    const availability = this.checkAvailability(visit);
    if (availability === 'event_busy') {
      return 'Appointment canceled';
    } else if (availability === 'event') {
      return 'Upcoming appointment';
    } else if (availability === 'event_available') {
      return 'Appointment done';
    }
    return 'Error';
  }
}
