package pl.dmcs.springbootjsp_iwa.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;
import pl.dmcs.springbootjsp_iwa.model.Doctor;
import pl.dmcs.springbootjsp_iwa.model.User;

import java.util.Optional;

@Repository
public interface DoctorRepository extends JpaRepository<Doctor, Long> {
    Optional<Doctor> findDoctorByUser(User user);
    Boolean existsByFirstNameAndLastNameAndIdNot(String firstName, String lastName, Long id);
    Boolean existsByFirstNameAndLastName(String firstName, String lastName);
}
