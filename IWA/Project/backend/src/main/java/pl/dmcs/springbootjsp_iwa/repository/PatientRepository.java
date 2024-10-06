package pl.dmcs.springbootjsp_iwa.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.dmcs.springbootjsp_iwa.model.Patient;
import pl.dmcs.springbootjsp_iwa.model.User;

import java.util.Optional;

public interface PatientRepository extends JpaRepository<Patient, Long> {
    Optional<Patient> findPatientByUser(User user);
    Boolean existsByFirstNameAndLastNameAndIdNot(String firstName, String lastName, Long id);
    Boolean existsByFirstNameAndLastName(String firstName, String lastName);
}
