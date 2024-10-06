package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.Account;
import pl.dmcs.springbootjsp_iwa.repository.AccountRepository;

import java.util.List;
import java.util.Map;
import java.util.Optional;

@RestController
@RequestMapping("accounts")
public class AccountRESTController {
    private AccountRepository accountRepository;
    @Autowired
    public AccountRESTController(AccountRepository accountRepository) {
        this.accountRepository = accountRepository;
    }
    @RequestMapping(method = RequestMethod.GET)
    public List<Account> findAllAccounts() {
        return accountRepository.findAll();
    }
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public Optional<Account> findAccount(@PathVariable("id") long id) {
        return accountRepository.findById(id);
    }
    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Account> addAccount(@RequestBody Account account) {
        accountRepository.save(account);
        return new ResponseEntity<>(account, HttpStatus.CREATED);
    }
    @RequestMapping(value = "/{id}", method = RequestMethod.DELETE)
    public ResponseEntity<Account> deleteAccount(@PathVariable("id") long id) {
        Optional<Account> account = accountRepository.findById(id);
        if (account.isEmpty()) {
            System.out.println("Account not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        accountRepository.deleteById(id);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(method = RequestMethod.DELETE)
    public ResponseEntity<Account> deleteAllAccounts() {
        accountRepository.deleteAll();
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    //@PutMapping("/{id}")
    public ResponseEntity<Account> updateAccount(@RequestBody Account account, @PathVariable("id") long id) {
        account.setId(id);
        accountRepository.save(account);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(method = RequestMethod.PUT)
    public ResponseEntity<Account> updateAllAccounts(@RequestBody List<Account> accounts) {
        accountRepository.deleteAll();
        List<Account> updatedAccounts = accountRepository.saveAll(accounts);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(value="/{id}", method = RequestMethod.PATCH)
    //@PatchMapping("/{id}")
    public ResponseEntity<Account> updatePartOfAccount(@RequestBody Map<String, Object> updates, @PathVariable("id") long id) {
        Optional<Account> account = accountRepository.findById(id);
        if (account.isEmpty()) {
            System.out.println("Account not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        partialUpdate(account.get(),updates);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    private void partialUpdate(Account account, Map<String, Object> updates) {
        if (updates.containsKey("accountName")) {
            account.setAccountName((String) updates.get("accountName"));
        }
        accountRepository.save(account);
    }
}
