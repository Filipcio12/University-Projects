package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.http.ResponseEntity;
import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.repository.*;

import java.util.HashMap;
import java.util.Map;

@RestController
@CrossOrigin(origins = "http://localhost:4200", maxAge = 3600)
@RequestMapping("/admin")
public class AdminRestController {
    private VisitRepository visitRepository;
    private DoctorRepository doctorRepository;
    private PatientRepository patientRepository;
    private UserRepository userRepository;
    private PrescriptionRepository prescriptionRepository;

    AdminRestController(VisitRepository visitRepository, DoctorRepository doctorRepository,
                       PatientRepository patientRepository, UserRepository userRepository,
                       PrescriptionRepository prescriptionRepository) {
        this.visitRepository = visitRepository;
        this.doctorRepository = doctorRepository;
        this.patientRepository = patientRepository;
        this.userRepository = userRepository;
        this.prescriptionRepository = prescriptionRepository;
    }

    @GetMapping("/status")
    @PreAuthorize("hasRole('ADMIN')")
    ResponseEntity<?> getStatus() {
        Map<String, Long> statusCounts = new HashMap<>();
        statusCounts.put("doctors", doctorRepository.count());
        statusCounts.put("patients", patientRepository.count());
        statusCounts.put("visits", visitRepository.count());
        statusCounts.put("prescriptions", prescriptionRepository.count());

        return ResponseEntity.ok(statusCounts);
    }
}
