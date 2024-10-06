package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.ModelAttribute;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMethod;
import pl.dmcs.springbootjsp_iwa.model.Fib;

@Controller
public class FibController {

    @RequestMapping("/fib")
    public String fib(Model model) {
        model.addAttribute("message","Find Fibonacci number given index.");
        Fib fib = new Fib();
        model.addAttribute("fib", fib);
        return "fib";
    }

    @RequestMapping(value = "/calcFib.html", method = RequestMethod.POST)
    public String calcFib(@ModelAttribute("fib") Fib fib) {
        String indexString = fib.getIndexString();

        int n = 1;
        try {
            n = Integer.parseInt(indexString);
            if (n < 1) {
                throw new Exception();
            }
        } catch (Exception ex) {
            System.out.println("Incorrect input");
            return "redirect:fib";
        }

        long result = Fib.calcFib(n);
        if (result < 0) {
            System.out.println("Overflow");
        } else {
            System.out.println(result);
        }

        return "redirect:fib";
    }

}
