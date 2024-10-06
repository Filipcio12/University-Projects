package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.Account;
import pl.dmcs.springbootjsp_iwa.model.Address;
import pl.dmcs.springbootjsp_iwa.repository.AddressRepository;

import java.util.List;
import java.util.Map;
import java.util.Optional;

@RestController
@RequestMapping("addresses")
public class AddressRESTController {
    private AddressRepository addressRepository;
    @Autowired
    public AddressRESTController(AddressRepository addressRepository) {
        this.addressRepository = addressRepository;
    }
    @RequestMapping(method = RequestMethod.GET)
    public List<Address> findAllAddresses() {
        return addressRepository.findAll();
    }
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public Optional<Address> findAddress (@PathVariable("id") long id) {
        return addressRepository.findById(id);
    }
    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Address> addAddress(@RequestBody Address address) {
        addressRepository.save(address);
        return new ResponseEntity<>(address, HttpStatus.CREATED);
    }
    @RequestMapping(value = "/{id}", method = RequestMethod.DELETE)
    public ResponseEntity<Address> deleteAddress(@PathVariable("id") long id) {
        Optional<Address> address = addressRepository.findById(id);
        if (address.isEmpty()) {
            System.out.println("Address not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        addressRepository.deleteById(id);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(method = RequestMethod.DELETE)
    public ResponseEntity<Account> deleteAllAddresses() {
        addressRepository.deleteAll();
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    //@PutMapping("/{id}")
    public ResponseEntity<Address> updateAccount(@RequestBody Address address, @PathVariable("id") long id) {
        address.setId(id);
        addressRepository.save(address);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(method = RequestMethod.PUT)
    public ResponseEntity<Address> updateAllAccounts(@RequestBody List<Address> addresses) {
        addressRepository.deleteAll();
        List<Address> updatedAddresses = addressRepository.saveAll(addresses);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(value="/{id}", method = RequestMethod.PATCH)
    //@PatchMapping("/{id}")
    public ResponseEntity<Address> updatePartOfAddress(@RequestBody Map<String, Object> updates, @PathVariable("id") long id) {
        Optional<Address> address = addressRepository.findById(id);
        if (address.isEmpty()) {
            System.out.println("Address not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        partialUpdate(address.get(),updates);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    private void partialUpdate(Address address, Map<String, Object> updates) {
        if (updates.containsKey("city")) {
            address.setCity((String) updates.get("city"));
        }
        if (updates.containsKey("street")) {
            address.setCity((String) updates.get("street"));
        }
        if (updates.containsKey("number")) {
            address.setCity((String) updates.get("number"));
        }
        if (updates.containsKey("postalCode")) {
            address.setCity((String) updates.get("postalCode"));
        }
        addressRepository.save(address);
    }
}
