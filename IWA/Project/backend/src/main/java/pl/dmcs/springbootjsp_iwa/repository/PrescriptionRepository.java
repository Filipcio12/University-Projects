package pl.dmcs.springbootjsp_iwa.repository;

import org.springframework.data.jpa.repository.JpaRepository;
import pl.dmcs.springbootjsp_iwa.model.Prescription;

public interface PrescriptionRepository extends JpaRepository<Prescription, Long> {
}
