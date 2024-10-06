package pl.dmcs.springbootjsp_iwa.controllers;

import org.apache.coyote.Request;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.Student;
import pl.dmcs.springbootjsp_iwa.repository.StudentRepository;
import java.util.List;
import java.util.Map;

@RestController
@RequestMapping("/students")
public class StudentRESTController {

    private StudentRepository studentRepository;

    @Autowired
    public StudentRESTController(StudentRepository studentRepository) {this.studentRepository = studentRepository;
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
        studentRepository.save(student);
        return new ResponseEntity<Student>(student, HttpStatus.CREATED);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.DELETE)
    //@DeleteMapping("/{id}")
    public ResponseEntity<Student> deleteStudent (@PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            System.out.println("Student not found!");
            return new ResponseEntity<Student>(HttpStatus.NOT_FOUND);
        }
        studentRepository.deleteById(id);
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    // Delete for the entire collection
    @RequestMapping(method = RequestMethod.DELETE)
    public ResponseEntity<Student> deleteAllStudents() {
        studentRepository.deleteAll();
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    //@PutMapping("/{id}")
    public ResponseEntity<Student> updateStudent(@RequestBody Student student, @PathVariable("id") long id) {
        student.setId(id);
        studentRepository.save(student);
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    // Put for the entire collection
    @RequestMapping(method = RequestMethod.PUT)
    public ResponseEntity<Student> updateAllStudents(@RequestBody List<Student> students) {
        studentRepository.deleteAll();
        List<Student> updatedStudents = studentRepository.saveAll(students);
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
    }

    @RequestMapping(value="/{id}", method = RequestMethod.PATCH)
    //@PatchMapping("/{id}")
    public ResponseEntity<Student> updatePartOfStudent(@RequestBody Map<String, Object> updates, @PathVariable("id") long id) {
        Student student = studentRepository.findById(id);
        if (student == null) {
            System.out.println("Student not found!");
            return new ResponseEntity<Student>(HttpStatus.NOT_FOUND);
        }
        partialUpdate(student,updates);
        return new ResponseEntity<Student>(HttpStatus.NO_CONTENT);
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
        studentRepository.save(student);
    }

}
