import { User } from "./user.model";

export class Doctor {
  id: number;
  user: User;
  firstName: string;
  lastName: string;
  specialization: string;

  constructor(id: number, user: User, firstname: string, lastname: string, specialization: string) {
    this.id = id;
    this.user = user;
    this.firstName = firstname;
    this.lastName = lastname;
    this.specialization = specialization;
  }
}