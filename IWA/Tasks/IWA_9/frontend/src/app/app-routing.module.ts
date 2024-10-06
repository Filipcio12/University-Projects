import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HeroesComponent } from './heroes/heroes.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { HeroDetailComponent } from './hero-detail/hero-detail.component';
import { StudentsComponent } from './students/students.component';
import { AccountsComponent } from './accounts/accounts.component';
import { HomeComponent } from './home/home.component';
import { UserComponent } from './user/user.component';
import { AdminComponent } from './admin/admin.component';
import { RoleGuard } from './guards/role.guard';
import { authGuard } from './guards/auth.guard';
import { LoginComponent } from './login/login.component';
import { RegisterComponent } from './register/register.component';

const routes: Routes = [
  {path: 'home', component: HomeComponent},
  {path: 'user', component: UserComponent, canActivate: [RoleGuard], data: { roles: ['ROLE_USER','ROLE_ADMIN'] },},
  {path: 'admin', component: AdminComponent, canActivate: [authGuard], data: { roles: ['ROLE_ADMIN'] },},
  {path: 'auth/login', component: LoginComponent},
  {path: 'signup', component: RegisterComponent},
  {path: 'students', component: StudentsComponent},
  {path: 'accounts', component: AccountsComponent},
  {path: 'heroes', component: HeroesComponent},
  {path: 'dashboard', component: DashboardComponent},
  {path: 'detail/:id', component: HeroDetailComponent},
  {path: '', redirectTo: '/home', pathMatch: 'full'},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
