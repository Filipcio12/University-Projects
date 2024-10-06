import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { FibFormComponent } from './fib-form/fib-form.component';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, FibFormComponent],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  title = 'fib';
}
