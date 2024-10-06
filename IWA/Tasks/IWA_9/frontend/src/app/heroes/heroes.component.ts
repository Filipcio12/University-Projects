import { Component } from '@angular/core';
import { HEROES } from '../mock-heroes';
import { Hero } from '../hero';
import { HeroService } from '../hero.service';
import { MessageService } from '../message.service';

@Component({
  selector: 'app-heroes',
  templateUrl: './heroes.component.html',
  styleUrls: ['./heroes.component.css'],
})
export class HeroesComponent {
  heroes: Hero[] = [];
  selectedHero?: Hero;
  draggedHero?: Hero;

  constructor(private heroService: HeroService, 
    private messageService: MessageService
  ) {

  }

  getHeroes(): void {
    this.heroService.getHeroes().
      subscribe(heroes => this.heroes = heroes);
  }

  ngOnInit(): void {
    this.getHeroes();
  }

  onSelect(hero: Hero): void {
    this.selectedHero = hero;
    this.messageService.add(`HeroesComponent: Selected hero  id=${hero.id}`);
  }

  onKeyDown(event: KeyboardEvent): void {
    if (event.key === "ArrowDown" && this.selectedHero) {
      event.preventDefault();  // Prevent default scrolling behavior
      const index = this.heroes.indexOf(this.selectedHero);
      const nextIndex = (index + 1) % this.heroes.length;
      this.selectedHero = this.heroes[nextIndex];
    }
    if (event.key === "ArrowUp" && this.selectedHero) {
      event.preventDefault();
      const index = this.heroes.indexOf(this.selectedHero);
      const prevIndex = index === 0 ? this.heroes.length - 1 : index - 1;
      this.selectedHero = this.heroes[prevIndex];
    }
  }

  allowDrop(event: DragEvent) {
    event.preventDefault();
  }

  drop(event: DragEvent, hero: Hero) {
    event.preventDefault();
    if (this.selectedHero) {
      const tempHero = this.selectedHero;
      
      const draggedIndex = this.heroes.indexOf(this.selectedHero);
      const droppedIndex = this.heroes.indexOf(hero);
      
      this.heroes[draggedIndex] = hero;
      this.heroes[droppedIndex] = tempHero;
      
    }
  }

}