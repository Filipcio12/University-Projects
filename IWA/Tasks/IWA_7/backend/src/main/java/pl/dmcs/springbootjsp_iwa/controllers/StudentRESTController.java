package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.Student;
import pl.dmcs.springbootjsp_iwa.repository.AddressRepository;
import pl.dmcs.springbootjsp_iwa.repository.StudentRepository;
import java.util.List;
import java.util.Map;

@RestController
@CrossOrigin(origins = "http://localhost:4200")
@RequestMapping("/students")
public class StudentRESTController {

    private StudentRepository studentRepository;
    private AddressRepository addressRepository;

    @Autowired
    public StudentRESTController(StudentRepository studentRepository, AddressRepository addressRepository) {
        this.studentRepository = studentRepository;
        this.addressRepository = addressRepository;
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
//        if (student.getAddress().getId() <= 0 )
//        {
//            addressRepository.save(student.getAddress());
//        }
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

    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    //@PutMapping("/{id}")
    public ResponseEntity<Student> updateStudent(@RequestBody Student student, @PathVariable("id") long id) {
        student.setId(id);
        studentRepository.save(student);
        return new ResponseEntity<>(student, HttpStatus.OK);
    }

    // Put for the entire collection
    @RequestMapping(method = RequestMethod.PUT)
    public ResponseEntity<List<Student>> updateAllStudents(@RequestBody List<Student> students) {
        studentRepository.deleteAll();
        List<Student> updatedStudents = studentRepository.saveAll(students);
        return new ResponseEntity<>(updatedStudents, HttpStatus.OK);
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
        return new ResponseEntity<>(student, HttpStatus.OK);
    }

    private void partialUpdate(Student student, Map<String, Object> updates) {
        if (updates.containsKey("firstname")) {
            String firstName = (String) updates.get("firstname");
            if (!firstName.isEmpty()) {
                student.setFirstname(firstName);
            }
        }
        if (updates.containsKey("lastname")) {
            String lastName = (String) updates.get("lastname");
            if (!lastName.isEmpty()) {
                student.setLastname(lastName);
            }
        }
        if (updates.containsKey("email")) {
            String email = (String) updates.get("email");
            if (!email.isEmpty()) {
                student.setEmail(email);
            }
        }
        if (updates.containsKey("telephone")) {
            String telephone = (String) updates.get("telephone");
            if (!telephone.isEmpty()) {
                student.setTelephone(telephone);
            }
        }
        studentRepository.save(student);
    }

    @RequestMapping(method = RequestMethod.DELETE)
    //@DeleteMapping("/{id}")
    public ResponseEntity<Student> deleteStudents() {
        studentRepository.deleteAll();
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }

}
