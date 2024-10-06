import { ComponentFixture, TestBed } from '@angular/core/testing';

import { FibFormComponent } from './fib-form.component';

describe('FibFormComponent', () => {
  let component: FibFormComponent;
  let fixture: ComponentFixture<FibFormComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      imports: [FibFormComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(FibFormComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
