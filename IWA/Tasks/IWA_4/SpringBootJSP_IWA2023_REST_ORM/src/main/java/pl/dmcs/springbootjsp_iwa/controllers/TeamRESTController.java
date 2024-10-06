package pl.dmcs.springbootjsp_iwa.controllers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import pl.dmcs.springbootjsp_iwa.model.Team;
import pl.dmcs.springbootjsp_iwa.repository.TeamRepository;

import java.util.List;
import java.util.Map;
import java.util.Optional;

@RestController
@RequestMapping("teams")
public class TeamRESTController {
    private TeamRepository teamRepository;
    @Autowired
    public TeamRESTController(TeamRepository teamRepository) {
        this.teamRepository = teamRepository;
    }
    @RequestMapping(method = RequestMethod.GET)
    public List<Team> findAllTeams() {
        return teamRepository.findAll();
    }
    @RequestMapping(value = "/{id}", method = RequestMethod.GET)
    public Optional<Team> findTeam (@PathVariable("id") long id) {
        return teamRepository.findById(id);
    }
    @RequestMapping(method = RequestMethod.POST)
    public ResponseEntity<Team> addTeam(@RequestBody Team team) {
        teamRepository.save(team);
        return new ResponseEntity<>(team, HttpStatus.CREATED);
    }
    @RequestMapping(value = "/{id}", method = RequestMethod.DELETE)
    public ResponseEntity<Team> deleteTeam(@PathVariable("id") long id) {
        Optional<Team> team = teamRepository.findById(id);
        if (team.isEmpty()) {
            System.out.println("Team not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        teamRepository.deleteById(id);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(method = RequestMethod.DELETE)
    public ResponseEntity<Team> deleteAllTeams() {
        teamRepository.deleteAll();
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(value="/{id}", method = RequestMethod.PUT)
    //@PutMapping("/{id}")
    public ResponseEntity<Team> updateTeam(@RequestBody Team team, @PathVariable("id") long id) {
        team.setId(id);
        teamRepository.save(team);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(method = RequestMethod.PUT)
    public ResponseEntity<Team> updateAllTeams(@RequestBody List<Team> teams) {
        teamRepository.deleteAll();
        List<Team> updatedTeams = teamRepository.saveAll(teams);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    @RequestMapping(value="/{id}", method = RequestMethod.PATCH)
    //@PatchMapping("/{id}")
    public ResponseEntity<Team> updatePartOfTeam(@RequestBody Map<String, Object> updates, @PathVariable("id") long id) {
        Optional<Team> team = teamRepository.findById(id);
        if (team.isEmpty()) {
            System.out.println("Team not found!");
            return new ResponseEntity<>(HttpStatus.NOT_FOUND);
        }
        partialUpdate(team.get(),updates);
        return new ResponseEntity<>(HttpStatus.NO_CONTENT);
    }
    private void partialUpdate(Team team, Map<String, Object> updates) {
        if (updates.containsKey("teamName")) {
            team.setTeamName((String) updates.get("teamName"));
        }
        teamRepository.save(team);
    }
}
