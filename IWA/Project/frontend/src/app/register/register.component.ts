import { Component, OnInit } from '@angular/core';
import {AuthService} from '../auth/auth.service';
import { Patient } from '../models/patient.model';
import { User } from '../models/user.model';

@Component({
  selector: 'app-register',
  templateUrl: './register.component.html',
  styleUrls: ['./register.component.css']
})
export class RegisterComponent implements OnInit {
  form: any = {};
  patient?: Patient;
  isSignedUp = false;
  isSignUpFailed = false;
  errorMessage = '';

  constructor(private authService: AuthService) { }

  ngOnInit() { }

  onSubmit() {
    console.log(this.form);

    this.patient = new Patient(
      0,
      new User(
        0,
        this.form.username,
        this.form.password
      ),
      this.form.firstName,
      this.form.lastName,
      ''
    );

    this.authService.registerPatient(this.patient).subscribe({
      next: (data) =>
    {
      console.log(data);
      this.isSignedUp = true;
      this.isSignUpFailed = false;
    }
  ,
    error: (error) => {
      console.log(error);
      this.errorMessage = error.error.message;
      this.isSignUpFailed = true;
    }
  });
  }
}
