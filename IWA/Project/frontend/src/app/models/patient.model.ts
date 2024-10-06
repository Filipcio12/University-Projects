import { User } from "./user.model";

export class Patient {
  id: number;
  user: User;
  firstName: string;
  lastName: string;
  medicalHistory: string;

  constructor(id: number, user: User, firstName: string, lastName: string, medicalHistory: string) {
    this.id = id;
    this.user = user;
    this.firstName = firstName;
    this.lastName = lastName;
    this.medicalHistory = medicalHistory;
  }
}