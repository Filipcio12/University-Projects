export class Account {
  id?: number;
  accountName: string;

  constructor(accountName: string) {
    this.accountName = accountName;
  }
}