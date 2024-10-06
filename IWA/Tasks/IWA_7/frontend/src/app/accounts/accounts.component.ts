import { Component, OnInit } from '@angular/core';
import { Account } from './account.model';
import { AccountService } from './account.service';

@Component({
  selector: 'app-accounts',
  templateUrl: './accounts.component.html',
  styleUrl: './accounts.component.css'
})
export class AccountsComponent implements OnInit {
  accountList?: Account[];
  account?: Account;

  constructor(private accountService: AccountService) {}

  ngOnInit(): void {
    this.getAccounts();
  }

  getAccounts(): void {
    this.accountService.getAccounts()
      .subscribe(accountList => this.accountList = accountList);
  }

  add(accountName: string): void {
    accountName = accountName.trim();
    this.accountService.addAccount({ accountName } as Account)
    .subscribe({ 
      next: (account: Account) => { this.accountList?.push(account); },
      error: () => {},
      complete: () => {
        if (this.accountList != undefined) {
          this.accountService.totalItems.next(this.accountList.length);
          console.log(this.accountList.length);
        }
      }
    });
  }

  delete(account: Account): void  {
    this.accountList = this.accountList?.filter(c => c !== account);
    this.accountService.deleteAccount(account).subscribe(() => {
        // for automatic update of number of accounts in parent component
      if (this.accountList != undefined) {
        this.accountService.totalItems.next(this.accountList.length);
        console.log(this.accountList.length);
      }
      }
    );
  }

  update(accountName: string, accountToUpdate: Account): void {
    let id = accountToUpdate.id;
    accountName = accountName.trim();
    console.log(id);

    if (id != undefined) {
      this.accountService.updateAccount({accountName} as Account, id)
        .subscribe({
          next: (account: Account) => {
            if (this.accountList != undefined) {
              let index = this.accountList?.indexOf(accountToUpdate);
              this.accountList[index] = account;
            }
          },
          error: () => {
          },
          complete: () => {
            if (this.accountList != undefined) {
              this.accountService.totalItems.next(this.accountList.length);
              console.log(this.accountList.length);
            }
          }
        })
    }
  }

  deleteAll(): void {
    this.accountService.deleteAccounts().subscribe(() => {
        if (this.accountList != undefined) {
          this.accountList.length = 0;
        }
      }
    );
  }


}
