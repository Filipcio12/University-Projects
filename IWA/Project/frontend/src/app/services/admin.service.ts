import { Injectable } from '@angular/core';
import { Observable } from 'rxjs';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class AdminService {

  private adminUrl = 'http://localhost:8080/admin';

  constructor(private http: HttpClient) { }

  getStatus(): Observable<object> {
    return this.http.get<object>(this.adminUrl + '/status')
  }

}
