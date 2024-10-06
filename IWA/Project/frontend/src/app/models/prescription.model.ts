import { Doctor } from "./doctor.model";
import { Patient } from "./patient.model";

export class Prescription {
  id: number;
  doctor: Doctor;
  patient: Patient;
  medication: string;
  description: string;
  
  constructor(id: number, doctor: Doctor, patient: Patient, medication: string, description: string,) {
    this.id = id;
    this.doctor = doctor;
    this.patient = patient;
    this.medication = medication;
    this.description = description;
  }
}