import { ComponentFixture, TestBed } from '@angular/core/testing';

import { UserVisitsComponent } from './user-visits.component';

describe('UserVisitsComponent', () => {
  let component: UserVisitsComponent;
  let fixture: ComponentFixture<UserVisitsComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [UserVisitsComponent]
    })
    .compileComponents();
    
    fixture = TestBed.createComponent(UserVisitsComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
