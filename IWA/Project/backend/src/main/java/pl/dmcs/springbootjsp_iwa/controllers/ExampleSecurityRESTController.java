package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.security.access.prepost.PreAuthorize;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.repository.UserRepository;
import pl.dmcs.springbootjsp_iwa.model.User;

import java.util.Optional;

@RestController
@CrossOrigin(origins = "http://localhost:4200", maxAge = 3600)
@RequestMapping("/exampleSecurity")
public class ExampleSecurityRESTController {

    private UserRepository userRepository;

    ExampleSecurityRESTController(UserRepository userRepository) {
        this.userRepository = userRepository;
    }

    @GetMapping("/user")
    @PreAuthorize("hasRole('USER') or hasRole('ADMIN')")
    public String userAccess() {
        return ">>> User Contents!";
    }

    @GetMapping("/admin")
    @PreAuthorize("hasRole('ADMIN')")
    public String adminAccess() {
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    return ">>> Admin Contents";
    }

    @GetMapping("/user/{userId}")
    @PreAuthorize("#userId == authentication.principal.id or hasRole('ADMIN')")
    public String getUserName(@PathVariable Long userId) {
        Optional<User> user = userRepository.findById(userId);
        if (user.isEmpty()) {
            return "";
        } else {
            return user.get().getUsername();
        }
    }

}
