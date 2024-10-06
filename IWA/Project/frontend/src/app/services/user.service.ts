import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { HttpClient } from '@angular/common/http';
import { User } from '../models/user.model';
import { Patient } from '../models/patient.model';
import { Doctor } from '../models/doctor.model';
import { HttpHeaders } from '@angular/common/http';

const httpOptions = {
  headers: new HttpHeaders({'Content-Type': 'application/json'})
};

@Injectable({
  providedIn: 'root'
})
export class UserService {

  private userUrl = 'http://localhost:8080/exampleSecurity/user';
  private adminUrl = 'http://localhost:8080/exampleSecurity/admin';
  private usersUrl = 'http://localhost:8080/users';

  constructor(private http: HttpClient) { }

  getUserPage(): Observable<string> {
    return this.http.get(this.userUrl, { responseType: 'text' });
  }

  getAdminPage(): Observable<string> {
    return this.http.get(this.adminUrl, { responseType: 'text' });
  }

  getUserData(): Patient {
    return new Patient(1, new User(2, "user1", "123456"), "Filip", "Fajfer", "penicillin allergy");
  }

  getPatient(username: string): Observable<Patient> {
    return this.http.get<Patient>(this.usersUrl + "/patient/" + username);
  }

  getPatients(): Observable<Patient[]> {
    return this.http.get<Patient[]>(this.usersUrl + "/patient");
  }

  getDoctor(username: string): Observable<Doctor> {
    return this.http.get<Doctor>(this.usersUrl + "/doctor/" + username);
  }

  getDoctors(): Observable<Doctor[]> {
    return this.http.get<Doctor[]>(this.usersUrl + "/doctor");
  }

  getDoctorByID(id: number): Observable<Doctor> {
    return this.http.get<Doctor>(this.usersUrl + "/doctor/id/" + id);
  }

  getPatientByID(id: number): Observable<Patient> {
    return this.http.get<Patient>(this.usersUrl + "/patient/id/" + id);
  }

  updateDoctor(doctor: Doctor, id: number): Observable<Doctor> {
    return this.http.put<Doctor>(this.usersUrl + "/doctor/update/" + id, doctor, httpOptions);
  }

  updatePatient(patient: Patient, id: number): Observable<Patient> {
    return this.http.put<Patient>(this.usersUrl + "/patient/update/" + id, patient, httpOptions);
  }
}
