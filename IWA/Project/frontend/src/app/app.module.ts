import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';
import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { FormsModule, ReactiveFormsModule } from '@angular/forms';
import { HttpClientModule } from '@angular/common/http';
import { HomeComponent } from './home/home.component';
import { LoginComponent } from './login/login.component';
import { RegisterComponent } from './register/register.component';
import { AdminComponent } from './admin/admin.component';
import { UserComponent } from './user/user.component';
import { httpInterceptorProviders } from './auth/auth.interceptor';
import { HomePageComponent } from './home-page/home-page.component';
import { TitleComponent } from './title/title.component';
import { provideAnimationsAsync } from '@angular/platform-browser/animations/async';
import { MatSidenavModule } from '@angular/material/sidenav';
import { UserPanelComponent } from './user-panel/user-panel.component';
import { UserHomeComponent } from './user-home/user-home.component';
import { MatIconModule } from '@angular/material/icon';
import { MatInputModule } from '@angular/material/input';
import { MatCardModule } from '@angular/material/card';
import { MatButtonModule } from '@angular/material/button';
import { MatTableModule } from '@angular/material/table';
import { UserVisitsComponent } from './user-visits/user-visits.component';
import { MatSortModule } from '@angular/material/sort';
import { MatFormFieldModule } from '@angular/material/form-field';
import { VisitDetailComponent } from './visit-detail/visit-detail.component';
import { MatSelectModule } from '@angular/material/select';
import { MatTooltip } from '@angular/material/tooltip';
import { MatDatepickerModule } from '@angular/material/datepicker';
import { MatNativeDateModule } from '@angular/material/core';
import { ProfileComponent } from './profile/profile.component';
import { DoctorsComponent } from './doctors/doctors.component';
import { PatientsComponent } from './patients/patients.component';
import { DoctorDetailComponent } from './doctor-detail/doctor-detail.component';
import { PatientDetailComponent } from './patient-detail/patient-detail.component';

@NgModule({
  declarations: [
    AppComponent,
    HomeComponent,
    LoginComponent,
    RegisterComponent,
    AdminComponent,
    UserComponent,
    UserPanelComponent,
    HomePageComponent,
    TitleComponent,
    UserHomeComponent,
    UserVisitsComponent,
    VisitDetailComponent,
    ProfileComponent,
    DoctorsComponent,
    PatientsComponent,
    DoctorDetailComponent,
    PatientDetailComponent,
  ],
  imports: [
    BrowserModule,
    FormsModule,
    AppRoutingModule,
    HttpClientModule,
    MatSidenavModule,
    MatIconModule,
    MatCardModule,
    ReactiveFormsModule,
    MatDatepickerModule,
    MatNativeDateModule,
    MatSelectModule,
    MatButtonModule,
    MatInputModule,
    MatTableModule,
    MatSortModule,
    MatFormFieldModule,
    MatTooltip,
  ],
  providers: [httpInterceptorProviders, provideAnimationsAsync()],
  bootstrap: [AppComponent]
})
export class AppModule { }
