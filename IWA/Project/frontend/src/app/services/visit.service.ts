import { Injectable } from '@angular/core';
import { Observable, tap } from 'rxjs';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Visit } from '../models/visit.model';
import { of, catchError } from 'rxjs';

const httpOptions = {
  headers: new HttpHeaders({'Content-Type': 'application/json'})
};

@Injectable({
  providedIn: 'root'
})
export class VisitService {

  private visitUrl = 'http://localhost:8080/visits';

  constructor(private http: HttpClient) { }

  getPatientVisit(username: string, id: number): Observable<Visit> {
    return this.http.get<Visit>(this.visitUrl + "/patient/" + username + "/" + id);
  }

  getPatientVisits(username: string): Observable<Visit[]> {
    return this.http.get<Visit[]>(this.visitUrl + "/patient/" + username);
  }

  getDoctorVisit(username: string, id: number): Observable<Visit> {
    return this.http.get<Visit>(this.visitUrl + "/doctor/" + username + "/" + id);
  }

  getDoctorVisits(username: string): Observable<Visit[]> {
    return this.http.get<Visit[]>(this.visitUrl + "/doctor/" + username);
  }

  getVisit(id: number): Observable<Visit> {
    return this.http.get<Visit>(this.visitUrl + "/admin/" + id);
  }

  getAllVisits(): Observable<Visit[]> {
    return this.http.get<Visit[]>(this.visitUrl + "/admin");
  }

  getUpcomingPatientVisits(username: string): Observable<Visit[]> {
    return this.http.get<Visit[]>(this.visitUrl + "/upcoming/patient/" + username);
  }

  getUpcomingDoctorVisits(username: string): Observable<Visit[]> {
    return this.http.get<Visit[]>(this.visitUrl + "/upcoming/doctor/" + username);
  }

  getAllUpcomingVisits(): Observable<Visit[]> {
    return this.http.get<Visit[]>(this.visitUrl + "/upcoming/admin");
  }

  updateVisit(visit: Visit, id: number): Observable<Visit> {
    return this.http.put<Visit>(this.visitUrl + "/" + id, visit, httpOptions).pipe(
      tap(_ => this.log(`updated visit id=${visit.id}`)),
      catchError(this.handleError<any>('updateVisit'))
    );
  }

  addVisit(visit: Visit): Observable<Visit> {
    return this.http.post<Visit>(this.visitUrl, visit, httpOptions).pipe(
      tap(_ => this.log(`added visit id=${visit.id}`)),
      catchError(this.handleError<any>('addedVisit'))
    );
  }

  cancelVisit(username: string, id: number): Observable<Visit> {
    return this.http.patch<Visit>(this.visitUrl + "/cancel/" + username + "/" + id, httpOptions).pipe(
      tap(_ => this.log(`canceled visit id=${id}`)),
      catchError(this.handleError<any>('canceledVisit'))
    ); 
  }

  private handleError<T>(operation = 'operation', result?: T) {
    return (error: any): Observable<T> => {

      // TODO: send the error to remote logging infrastructure
      console.error(error); // log to console instead

      // TODO: better job of transforming error for user consumption
      this.log(`${operation} failed: ${error.message}`);

      // Let the app keep running by returning an empty result.
      return of(result as T);
    };
  }

  private log(message: string) {
    console.log('VisitService: ' + message);
  }
}
