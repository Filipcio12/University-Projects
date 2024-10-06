import { Doctor } from "./doctor.model";
import { Patient } from "./patient.model";
import { Prescription } from "./prescription.model";

export class Visit {
  id: number;
  doctor: Doctor;
  patient: Patient;
  prescription: Prescription;
  visitDate: Date;
  notes: string;
  isCanceled: boolean;

  constructor(id: number, doctor: Doctor, patient: Patient, prescription: Prescription, visitDate: Date, notes: string, isCanceled: boolean) {
    this.id = id;
    this.doctor = doctor;
    this.patient = patient;
    this.prescription = prescription;
    this.visitDate = visitDate;
    this.notes = notes;
    this.isCanceled = isCanceled;
  }
}