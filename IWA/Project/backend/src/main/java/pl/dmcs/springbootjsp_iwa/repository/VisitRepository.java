package pl.dmcs.springbootjsp_iwa.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.dmcs.springbootjsp_iwa.model.Doctor;
import pl.dmcs.springbootjsp_iwa.model.Patient;
import pl.dmcs.springbootjsp_iwa.model.Visit;

import javax.print.Doc;
import java.util.Date;
import java.util.List;
import java.util.Optional;

public interface VisitRepository extends JpaRepository<Visit, Long> {
    List<Visit> findAllByPatient(Patient patient);
    List<Visit> findAllByDoctor(Doctor doctor);
    List<Visit> findByPatientAndVisitDateGreaterThanOrderByVisitDateAsc(Patient patient, Date current);
    List<Visit> findByDoctorAndVisitDateGreaterThanOrderByVisitDateAsc(Doctor doctor, Date current);
    List<Visit> findByVisitDateGreaterThanOrderByVisitDateAsc(Date current);
    Optional<Visit> findByPatientAndId(Patient patient, Long id);
    Optional<Visit> findByDoctorAndId(Doctor doctor, Long id);
    boolean existsByDoctorAndVisitDateBetweenAndIdNot(Doctor doctor, Date start, Date end, Long id);
    boolean existsByPatientAndVisitDateBetweenAndIdNot(Patient patient, Date start, Date end, Long id);
    boolean existsByDoctorAndVisitDateBetween(Doctor doctor, Date start, Date end);
    boolean existsByPatientAndVisitDateBetween(Patient patient, Date start, Date end);

}
