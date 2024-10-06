import { Component } from '@angular/core';
import { NgFor } from '@angular/common';
import { UserItemComponent } from '../user-item/user-item.component';

@Component({
  selector: 'app-user-list',
  standalone: true,
  imports: [NgFor, UserItemComponent],
  templateUrl: './user-list.component.html',
  styleUrl: './user-list.component.css'
})
export class UserListComponent {
  names: string[];

  constructor() {
    this.names = ['Filip', 'Mateusz', 'Kuba', 'Marcin'];
  }
}
