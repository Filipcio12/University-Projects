package pl.dmcs.springbootjsp_iwa.controllers;

import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.Account;
import pl.dmcs.springbootjsp_iwa.model.Address;
import pl.dmcs.springbootjsp_iwa.model.Student;
import pl.dmcs.springbootjsp_iwa.model.Team;
import pl.dmcs.springbootjsp_iwa.repository.AccountRepository;
import pl.dmcs.springbootjsp_iwa.repository.AddressRepository;
import pl.dmcs.springbootjsp_iwa.repository.StudentRepository;
import pl.dmcs.springbootjsp_iwa.repository.TeamRepository;

import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/students")
public class StudentRESTController {

    private StudentRepository studentRepository;
    private AddressRepository addressRepository;
    private AccountRepository accountRepository;
    private TeamRepository teamRepository;

    @Autowired
    public StudentRESTController(StudentRepository studentRepository, AddressRepository addressRepository,
                                 AccountRepository accountRepository, TeamRepository teamRepository) {
        this.studentRepository = studentRepository;
        this.addressRepository = addressRepository;
        this.accountRepository = accountRepository;
        this.teamRepository = teamRepository;
    }

    @RequestMapping(method = RequestMethod.GET/*, produces = "application/xml"*/)
    //@GetMapping
    public List<Student> findAllStudents() { return studentRepository.findAll();
    }

    // GET for a single object
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public Student findOneStudent(@PathVariable("id") long id) {
        return studentRepository.findById(id);
    }

    @RequestMapping(method = RequestMethod.POST)
    //@PostMapping
    public ResponseEntity<Student> addStudent(@RequestBody Student student) {

        // Commented out due to simplify http requests sent from angular app
        if (student.getAddress() != null && student.getAddress().getId() <= 0 )
        {
            addressRepository.save(student.getAddress());
        }

        if (student.getTeamList() != null) {
            List<Team> teamList = student.getTeamList();

            for (Team team : teamList) {
                if (team.getId() <= 0) {
                    teamRepository.save(team);
                }
            }
        }
        // Commented out due to simplify http requests sent from angular app
        studentRepository.save(student);
        return new ResponseEntity<>(student, HttpStatus.CREATED);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.DELETE)
    //@DeleteMapping("/{id}")
    public ResponseEntity<Student> deleteStudent (@PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            System.out.println("Student not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        studentRepository.deleteById(id);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

    // Delete for the entire collection
    @RequestMapping(method = RequestMethod.DELETE)
    public ResponseEntity<Student> deleteAllStudents() {
        studentRepository.deleteAll();
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    @Transactional
    //@PutMapping("/{id}")
    public ResponseEntity<Student> updateStudent(@RequestBody Student newStudent, @PathVariable("id") long id) {
        Student oldStudent = studentRepository.findById(id);

        if (oldStudent == null) {
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }

        // Account
        Account oldAccount = oldStudent.getAccount();
        Account newAccount = newStudent.getAccount();

        if (newAccount != null && newAccount.getId() != oldAccount.getId()) {
            accountRepository.delete(oldAccount);
        }

        newStudent.setId(id);
        studentRepository.save(newStudent);
        return new ResponseEntity<>(newStudent, HttpStatus.NO_CONTENT);
    }

    // Put for the entire collection
    @RequestMapping(method = RequestMethod.PUT)
    public ResponseEntity<Student> updateAllStudents(@RequestBody List<Student> students) {
        studentRepository.deleteAll();
        List<Student> updatedStudents = studentRepository.saveAll(students);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.PATCH)
    //@PatchMapping("/{id}")
    public ResponseEntity<Student> updatePartOfStudent(@RequestBody Map<String, Object> updates, @PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            System.out.println("Student not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        partialUpdate(student,updates);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

    private void partialUpdate(Student student, Map<String, Object> updates) {
        if (updates.containsKey("firstname")) {
            student.setFirstname((String) updates.get("firstname"));
        }
        if (updates.containsKey("lastname")) {
            student.setLastname((String) updates.get("lastname"));
        }
        if (updates.containsKey("email")) {
            student.setEmail((String) updates.get("email"));
        }
        if (updates.containsKey("telephone")) {
            student.setTelephone((String) updates.get("telephone"));
        }

        if (updates.containsKey("account")) {
            Map<String, Object> accountUpdates = (Map<String, Object>) updates.get("account");
            Account account = student.getAccount();

            if (account != null) {
                if (accountUpdates.containsKey("accountName")) {
                    account.setAccountName((String) accountUpdates.get("accountName"));
                }
                accountRepository.save(account);
            }
        }

        if (updates.containsKey("address")) {
            Map<String, Object> addressUpdates = (Map<String, Object>) updates.get("address");
            Address currentAddress = student.getAddress();

            Address newAddress = new Address();

            newAddress.setCity((String) addressUpdates.get("city"));
            newAddress.setStreet((String) addressUpdates.get("street"));
            newAddress.setNumber((String) addressUpdates.get("number"));
            newAddress.setPostalCode((String) addressUpdates.get("postalCode"));

            Address address = addressRepository.findByCityAndAndStreetAndNumberAndPostalCode(newAddress.getCity(), newAddress.getStreet(),
                    newAddress.getNumber(), newAddress.getPostalCode());

            currentAddress.setCity(newAddress.getCity());
            currentAddress.setStreet(newAddress.getStreet());
            currentAddress.setNumber(newAddress.getNumber());
            currentAddress.setPostalCode(newAddress.getPostalCode());

            if (address == null) {
                addressRepository.save(newAddress);
            }
        }

        studentRepository.save(student);
    }
}
