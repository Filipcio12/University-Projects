import { NgModule } from '@angular/core';
import { ResolveStart, RouterModule, Routes } from '@angular/router';
import { authGuard } from './guards/auth.guard';
import { LoginComponent } from './login/login.component';
import { RegisterComponent } from './register/register.component';
import { HomePageComponent } from './home-page/home-page.component';
import { TitleComponent } from './title/title.component';
import { UserPanelComponent } from './user-panel/user-panel.component';
import { UserHomeComponent } from './user-home/user-home.component';
import { UserVisitsComponent } from './user-visits/user-visits.component';
import { VisitDetailComponent } from './visit-detail/visit-detail.component';
import { ProfileComponent } from './profile/profile.component';
import { DoctorsComponent } from './doctors/doctors.component';
import { PatientsComponent } from './patients/patients.component';
import { DoctorDetailComponent } from './doctor-detail/doctor-detail.component';
import { PatientDetailComponent } from './patient-detail/patient-detail.component';

const routes: Routes = [
  {path: '', redirectTo: '/home', pathMatch: 'full'},
  {path: 'home', component: HomePageComponent, children:
    [
      {path: '', component: TitleComponent},
      {path: 'login', component: LoginComponent},
      {path: 'signup', component: RegisterComponent}
    ]
  },
  {path: 'user-panel', component: UserPanelComponent, canActivate: [authGuard], data: {roles: ['ROLE_USER', 'ROLE_DOCTOR', 'ROLE_ADMIN']}, children:
    [
      {path: '', component: UserHomeComponent},
      {path: 'visits', component: UserVisitsComponent},
      {path: 'visit-detail/:id', component: VisitDetailComponent},
      {path: 'visit-detail/new', component: VisitDetailComponent, canActivate: [authGuard], data: {roles: ['ROLE_DOCTOR', 'ROLE_ADMIN']}},
      {path: 'profile', component: ProfileComponent},
      {path: 'doctors', component: DoctorsComponent},
      {path: 'patients', component: PatientsComponent, canActivate: [authGuard], data: {roles: ['ROLE_DOCTOR', 'ROLE_ADMIN']}},
      {path: 'doctor-detail/:id', component: DoctorDetailComponent},
      {path: 'doctor-detail/new', component: DoctorDetailComponent},
      {path: 'patient-detail/:id', component: PatientDetailComponent, canActivate: [authGuard], data: {roles: ['ROLE_ADMIN', 'ROLE_DOCTOR']}},
      {path: 'patient-detail/new', component: PatientDetailComponent, canActivate: [authGuard], data: {roles: ['ROLE_ADMIN', 'ROLE_DOCTOR']}},
    ]
  },

];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
