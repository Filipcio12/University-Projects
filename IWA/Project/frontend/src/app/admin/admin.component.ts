import { Component, OnInit } from '@angular/core';
import {UserService} from '../services/user.service';

@Component({
  selector: 'app-admin',
  templateUrl: './admin.component.html',
  styleUrls: ['./admin.component.css']
})
export class AdminComponent implements OnInit {
  board?: string;
  errorMessage?: string;

  constructor(private userService: UserService) { }

  ngOnInit() {
    this.userService.getAdminPage().subscribe({
      next:(data) => {
        this.board = data;
      },
      error: (error) => {
        this.errorMessage = `${error.status}: ${JSON.parse(error.error).message}`;
      }
  });
  }

}
