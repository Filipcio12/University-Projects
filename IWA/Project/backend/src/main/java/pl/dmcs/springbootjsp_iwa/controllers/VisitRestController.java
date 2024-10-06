package pl.dmcs.springbootjsp_iwa.controllers;

import org.apache.coyote.Response;
import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.*;
import pl.dmcs.springbootjsp_iwa.repository.*;

import java.util.Date;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

@RestController
@CrossOrigin(origins = "http://localhost:4200", maxAge = 3600)
@RequestMapping("/visits")
public class VisitRestController {

    private VisitRepository visitRepository;
    private DoctorRepository doctorRepository;
    private PatientRepository patientRepository;
    private UserRepository userRepository;
    private PrescriptionRepository prescriptionRepository;

    VisitRestController(VisitRepository visitRepository, DoctorRepository doctorRepository,
                        PatientRepository patientRepository, UserRepository userRepository,
                        PrescriptionRepository prescriptionRepository) {
        this.visitRepository = visitRepository;
        this.doctorRepository = doctorRepository;
        this.patientRepository = patientRepository;
        this.userRepository = userRepository;
        this.prescriptionRepository = prescriptionRepository;
    }

    @GetMapping("/patient/{username}/{id}")
    @PreAuthorize("#username == authentication.principal.username or hasRole('DOCTOR') or hasRole('ADMIN')")
    ResponseEntity<Visit> getPatientVisit(@PathVariable String username, @PathVariable Long id) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Patient> patient = patientRepository.findPatientByUser(user.get());
        if (patient.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Visit> visit = visitRepository.findByPatientAndId(patient.get(), id);
        if (visit.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(visit.get());
    }

    @GetMapping("/patient/{username}")
    @PreAuthorize("#username == authentication.principal.username or hasRole('DOCTOR') or hasRole('ADMIN')")
    ResponseEntity<List<Visit>> getPatientVisits(@PathVariable String username) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Patient> patient = patientRepository.findPatientByUser(user.get());
        if (patient.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        List<Visit> visits = visitRepository.findAllByPatient(patient.get());
        if (visits.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(visits);
    }

    @GetMapping("/doctor/{username}/{id}")
    @PreAuthorize("(#username == authentication.principal.username and hasRole('DOCTOR')) or hasRole('ADMIN')")
    ResponseEntity<Visit> getDoctorVisit(@PathVariable String username, @PathVariable Long id) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Doctor> doctor = doctorRepository.findDoctorByUser(user.get());
        if (doctor.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Visit> visit = visitRepository.findByDoctorAndId(doctor.get(), id);
        if (visit.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(visit.get());
    }

    @GetMapping("/doctor/{username}")
    @PreAuthorize("(#username == authentication.principal.username and hasRole('DOCTOR')) or hasRole('ADMIN')")
    ResponseEntity<List<Visit>> getDoctorVisits(@PathVariable String username) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Doctor> doctor = doctorRepository.findDoctorByUser(user.get());
        if (doctor.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        List<Visit> visits = visitRepository.findAllByDoctor(doctor.get());
        if (visits.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(visits);
    }

    @GetMapping("/admin/{id}")
    @PreAuthorize("hasRole('ADMIN')")
    ResponseEntity<Visit> getVisit(@PathVariable Long id) {
        Optional<Visit> visit = visitRepository.findById(id);
        if (visit.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(visit.get());
    }

    @GetMapping("/admin")
    @PreAuthorize("hasRole('ADMIN')")
    ResponseEntity<List<Visit>> getAllVisits() {
        return ResponseEntity.ok(visitRepository.findAll());
    }

    @GetMapping("/upcoming/patient/{username}")
    @PreAuthorize("#username == authentication.principal.username or hasRole('DOCTOR') or hasRole('ADMIN')")
    ResponseEntity<List<Visit>> getUpcomingPatientVisits(@PathVariable String username) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Patient> patient = patientRepository.findPatientByUser(user.get());
        if (patient.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Date current = new Date();
        List<Visit> visits = visitRepository.findByPatientAndVisitDateGreaterThanOrderByVisitDateAsc(patient.get(), current);
        if (visits.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(visits);
    }

    @GetMapping("/upcoming/doctor/{username}")
    @PreAuthorize("(#username == authentication.principal.username and hasRole('DOCTOR')) or hasRole('ADMIN')")
    ResponseEntity<List<Visit>> getUpcomingDoctorVisits(@PathVariable String username) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Optional<Doctor> doctor = doctorRepository.findDoctorByUser(user.get());
        if (doctor.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        Date current = new Date();
        List<Visit> visits = visitRepository.findByDoctorAndVisitDateGreaterThanOrderByVisitDateAsc(doctor.get(), current);
        if (visits.isEmpty()) {
            return ResponseEntity.notFound().build();
        }
        return ResponseEntity.ok(visits);
    }

    @GetMapping("/upcoming/admin")
    @PreAuthorize("hasRole('ADMIN')")
    ResponseEntity<List<Visit>> getAllUpcomingVisits() {
        Date current = new Date();
        return ResponseEntity.ok(visitRepository.findByVisitDateGreaterThanOrderByVisitDateAsc(current));
    }

    @PutMapping("/{id}")
    @PreAuthorize("hasRole('DOCTOR') or hasRole('ADMIN')")
    public ResponseEntity<?> updateVisit(@RequestBody Visit visit, @PathVariable Long id) {
        Long visitId = visit.getId();
        if (!Objects.equals(visitId, id)) {
            return ResponseEntity.badRequest().body("ID mismatch error");
        }

        Patient patient = visit.getPatient();
        Doctor doctor = visit.getDoctor();
        Prescription prescription = visit.getPrescription();

        if (!patientRepository.existsById(patient.getId()) || !doctorRepository.existsById(doctor.getId())) {
            return ResponseEntity.badRequest().body("Doctor or patient not found");
        }

        Date visitDate = visit.getVisitDate();
        Date MinBefore = new Date(visitDate.getTime() - 29 * 60 * 1000);
        Date MinAfter = new Date(visitDate.getTime() + 29 * 60 * 1000);

        boolean doctorScheduleConflict = visitRepository.existsByDoctorAndVisitDateBetweenAndIdNot(doctor, MinBefore, MinAfter, id);
        boolean patientScheduleConflict = visitRepository.existsByPatientAndVisitDateBetweenAndIdNot(patient, MinBefore, MinAfter, id);

        if (doctorScheduleConflict || patientScheduleConflict) {
            return ResponseEntity.badRequest().body("Schedule conflict: Another visit exists within 15 minutes for doctor or patient");
        }

        if (prescription == null || !prescriptionRepository.existsById(prescription.getId()) ||
                !doctor.getId().equals(prescription.getDoctor().getId()) ||
                !patient.getId().equals(prescription.getPatient().getId())) {
            return ResponseEntity.badRequest().body("Prescription invalid");
        }

        prescriptionRepository.save(prescription);
        Visit updatedVisit = visitRepository.save(visit);

        return ResponseEntity.ok(updatedVisit);
    }

    @PostMapping()
    @PreAuthorize("hasRole('DOCTOR') or hasRole('ADMIN')")
    public ResponseEntity<?> addVisit(@RequestBody Visit visit) {
        Patient patient = visit.getPatient();
        Doctor doctor = visit.getDoctor();
        Prescription prescription = visit.getPrescription();

        if (!patientRepository.existsById(patient.getId()) || !doctorRepository.existsById(doctor.getId())) {
            System.out.println("Doctor or patient not found");
            return ResponseEntity.badRequest().body("Doctor or patient not found");
        }

        Date visitDate = visit.getVisitDate();
        Date fifteenMinBefore = new Date(visitDate.getTime() - 29 * 60 * 1000);
        Date fifteenMinAfter = new Date(visitDate.getTime() + 29 * 60 * 1000);
        Date currentDate = new Date();

        if (visitDate.before(currentDate)) {
            return ResponseEntity.badRequest().body("Date in the past");
        }

        boolean doctorScheduleConflict = visitRepository.existsByDoctorAndVisitDateBetween(doctor, fifteenMinBefore, fifteenMinAfter);
        boolean patientScheduleConflict = visitRepository.existsByPatientAndVisitDateBetween(patient, fifteenMinBefore, fifteenMinAfter);

        if (doctorScheduleConflict || patientScheduleConflict) {
            return ResponseEntity.badRequest().body("Schedule conflict: Another visit exists within 15 minutes for doctor or patient");
        }

        if (prescription == null ||
                !doctor.getId().equals(prescription.getDoctor().getId()) ||
                !patient.getId().equals(prescription.getPatient().getId())) {
            System.out.println("Prescription invalid");
            return ResponseEntity.badRequest().body("Prescription invalid");
        }

        prescription = prescriptionRepository.save(prescription);
        visit.setPrescription(prescription);
        Visit updatedVisit = visitRepository.save(visit);

        return ResponseEntity.ok(updatedVisit);
    }

    @PatchMapping("/cancel/{username}/{id}")
    @PreAuthorize("#username == authentication.principal.username and hasRole('USER')") // Adjust the roles as necessary
    public ResponseEntity<?> cancelVisit(@PathVariable String username, @PathVariable Long id) {
        Optional<User> user = userRepository.findByUsername(username);
        if (user.isEmpty()) {
            System.out.println("User empty");
            return ResponseEntity.notFound().build();
        }
        Optional<Patient> patient = patientRepository.findPatientByUser(user.get());
        if (patient.isEmpty()) {
            System.out.println("Patient empty");
            return ResponseEntity.notFound().build();
        }
        Optional<Visit> v = visitRepository.findByPatientAndId(patient.get(), id);
        if (v.isEmpty()) {
            System.out.println("Visit empty");
            return ResponseEntity.notFound().build();
        }
        Visit visit = v.get();
        visit.setIsCanceled(true);
        visitRepository.save(visit);
        return ResponseEntity.ok(visit);
    }
}
