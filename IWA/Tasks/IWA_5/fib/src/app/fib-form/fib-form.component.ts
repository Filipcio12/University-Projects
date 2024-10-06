import { Component } from '@angular/core';
import { Fib } from './fib';
import { NgIf } from '@angular/common';

@Component({
  selector: 'app-fib-form',
  standalone: true,
  imports: [NgIf],
  templateUrl: './fib-form.component.html',
  styleUrl: './fib-form.component.css'
})
export class FibFormComponent {
  fib: Fib;

  constructor() {
    this.fib = new Fib(0n);
  }

  calcFib(index: HTMLInputElement): boolean {
    const n = BigInt(index.value);
    this.fib = new Fib(n);
    return false;
  }
}
