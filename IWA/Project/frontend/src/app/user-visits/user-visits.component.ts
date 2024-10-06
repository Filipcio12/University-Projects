import { AfterViewInit, Component, OnInit, ViewChild } from '@angular/core';
import { Patient } from '../models/patient.model';
import { Doctor } from '../models/doctor.model';
import { Visit } from '../models/visit.model';
import { UserService } from '../services/user.service';
import { TokenStorageService } from '../auth/token-storage.service';
import { VisitService } from '../services/visit.service';
import { MatTableDataSource } from '@angular/material/table';
import { MatSort } from '@angular/material/sort';
import { Router } from '@angular/router';

@Component({
  selector: 'app-user-visits',
  templateUrl: './user-visits.component.html',
  styleUrl: './user-visits.component.css'
})
export class UserVisitsComponent implements OnInit, AfterViewInit {
  username?: string;
  user?: Patient | Doctor;
  roles: string[] = [];
  authority: string = '';
  visits: Visit[] = [];
  dataSource = new MatTableDataSource<Visit>();
  displayedColumns: string[] = ['doctor', 'patient', 'prescription', 'date', 'time', 'notes', 'isCanceled'];
  @ViewChild(MatSort, { static: true }) sort!: MatSort;

  constructor(private userService: UserService,
              private visitService: VisitService, 
              private tokenStorage: TokenStorageService,
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

  getPatientVisits() {
    this.username = this.tokenStorage.getUsername();
    this.visitService.getPatientVisits(this.username).subscribe(visits => {
      this.visits = visits.map(visit => this.transformVisit(visit));
      this.dataSource.data = this.visits;
    });
  }

  getDoctorVisits() {
    this.username = this.tokenStorage.getUsername();
    this.visitService.getDoctorVisits(this.username).subscribe(visits => {
      this.visits = visits.map(visit => this.transformVisit(visit));
      this.dataSource.data = this.visits;
    });
  }

  getAllVisits() {
    this.visitService.getAllVisits().subscribe(visits => {
      this.visits = visits.map(visit => this.transformVisit(visit));
      this.dataSource.data = this.visits;
    });
  }

  ngOnInit(): void {
    this.roles = this.tokenStorage.getAuthorities();
    this.determineAuthority();

    if (this.authority === 'user') {
      this.getPatient();
      this.getPatientVisits();
      console.log(this.visits);
    } else if (this.authority === 'doctor') {
      this.getDoctor();
      this.getDoctorVisits();
    } else if (this.authority === 'admin') {
      this.getAllVisits();
    }
  }

  ngAfterViewInit() {
    this.dataSource.sort = this.sort;
  }

  determineAuthority() {
    this.authority = this.roles.includes('ROLE_ADMIN') ? 'admin' :
                     this.roles.includes('ROLE_DOCTOR') ? 'doctor' : 'user';
  }

  applyFilter(event: Event): void {
    const filterValue = (event.target as HTMLInputElement).value;
    this.dataSource.filter = filterValue.trim().toLowerCase();
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
