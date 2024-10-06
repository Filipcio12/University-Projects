package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.security.core.parameters.P;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.Doctor;
import pl.dmcs.springbootjsp_iwa.model.Patient;
import pl.dmcs.springbootjsp_iwa.model.User;
import pl.dmcs.springbootjsp_iwa.repository.DoctorRepository;
import pl.dmcs.springbootjsp_iwa.repository.PatientRepository;
import pl.dmcs.springbootjsp_iwa.repository.UserRepository;
import pl.dmcs.springbootjsp_iwa.repository.VisitRepository;

import java.awt.geom.PathIterator;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

@RestController
@CrossOrigin(origins = "http://localhost:4200", maxAge = 3600)
@RequestMapping("/users")
public class UserRestController {
    private VisitRepository visitRepository;
    private DoctorRepository doctorRepository;
    private PatientRepository patientRepository;
    private UserRepository userRepository;

    UserRestController(VisitRepository visitRepository, DoctorRepository doctorRepository,
                        PatientRepository patientRepository, UserRepository userRepository) {
        this.visitRepository = visitRepository;
        this.doctorRepository = doctorRepository;
        this.patientRepository = patientRepository;
        this.userRepository = userRepository;
    }

    @GetMapping("/patient/{username}")
    @PreAuthorize("#username == authentication.principal.username or hasRole('DOCTOR') or hasRole('ADMIN')")
    ResponseEntity<Patient> getPatient(@PathVariable String username) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Patient> patient = patientRepository.findPatientByUser(user.get());
        if (patient.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(patient.get());
    }

    @GetMapping("/patient")
    @PreAuthorize("hasRole('DOCTOR') or hasRole('ADMIN')")
    ResponseEntity<List<Patient>> getPatients() {
        return ResponseEntity.ok(patientRepository.findAll());
    }

    @GetMapping("/doctor/{username}")
    ResponseEntity<Doctor> getDoctor(@PathVariable String username) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Doctor> doctor = doctorRepository.findDoctorByUser(user.get());
        if (doctor.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(doctor.get());
    }

    @GetMapping("/doctor")
    ResponseEntity<List<Doctor>> getDoctors() {
        return ResponseEntity.ok(doctorRepository.findAll());
    }

    @GetMapping("/doctor/id/{id}")
    ResponseEntity<Doctor> getDoctorByID(@PathVariable Long id) {
        Optional<Doctor> doctor = doctorRepository.findById(id);
        if (doctor.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(doctor.get());
    }

    @GetMapping("/patient/id/{id}")
    @PreAuthorize("hasRole('DOCTOR') or hasRole('ADMIN')")
    ResponseEntity<Patient> getPatientByID(@PathVariable Long id) {
        Optional<Patient> patient = patientRepository.findById(id);
        if (patient.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(patient.get());
    }

    @PutMapping("/doctor/update/{id}")
    @PreAuthorize("hasRole('ADMIN')")
    ResponseEntity<?> updateDoctor(@RequestBody Doctor doctor, @PathVariable Long id) {
        Long doctorId = doctor.getId();
        if (!Objects.equals(doctorId, id)) {
            return ResponseEntity.badRequest().body("ID mismatch error");
        }
        if (doctorRepository.existsByFirstNameAndLastNameAndIdNot(doctor.getFirstName(), doctor.getLastName(), id)) {
            return ResponseEntity.badRequest().body("Name conflict");
        }
        doctorRepository.save(doctor);
        return ResponseEntity.ok(doctor);
    }

    @PutMapping("/patient/update/{id}")
    @PreAuthorize("hasRole('ADMIN') or hasRole('DOCTOR')")
    ResponseEntity<?> updatePatient(@RequestBody Patient patient, @PathVariable Long id) {
        Long patientId = patient.getId();
        if (!Objects.equals(patientId, id)) {
            return ResponseEntity.badRequest().body("ID mismatch error");
        }
        if (patientRepository.existsByFirstNameAndLastNameAndIdNot(patient.getFirstName(), patient.getLastName(), id)) {
            return ResponseEntity.badRequest().body("Name conflict");
        }
        patientRepository.save(patient);
        return ResponseEntity.ok(patient);
    }
}
