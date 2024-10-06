import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { HeroesComponent } from './heroes/heroes.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { HeroDetailComponent } from './hero-detail/hero-detail.component';
import { StudentsComponent } from './students/students.component';
import { AccountsComponent } from './accounts/accounts.component';

const routes: Routes = [
  {path: '', redirectTo: '/students', pathMatch: 'full'},
  {path: 'students', component: StudentsComponent},
  {path: 'accounts', component: AccountsComponent},
  {path: 'heroes', component: HeroesComponent},
  {path: 'dashboard', component: DashboardComponent},
  {path: 'detail/:id', component: HeroDetailComponent},
];

@NgModule({
  imports: [RouterModule.forRoot(routes)],
  exports: [RouterModule]
})
export class AppRoutingModule { }
