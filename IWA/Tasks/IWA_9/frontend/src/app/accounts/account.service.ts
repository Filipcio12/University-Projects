import { Injectable } from '@angular/core';
import { HttpClient, HttpHeaders } from '@angular/common/http';
import { Account } from './account.model';
import { BehaviorSubject, catchError, Observable, of, tap} from 'rxjs';

const httpOptions = {
  headers: new HttpHeaders({ 'Content-Type': 'application/json' })
};

@Injectable({
  providedIn: 'root'
})
export class AccountService {
  private accountsUrl = "http://localhost:8080/accounts";

  constructor(private http: HttpClient) { }

  getAccounts(): Observable<Account[]> {
    return this.http.get<Account[]>(this.accountsUrl);
  }

  /** POST: add a new Account to the server */
  addAccount(account: Account): Observable<Account> {
    return this.http.post<Account>(this.accountsUrl, account, httpOptions).pipe(
      tap((accountAdded: Account) => this.log(`added account id=${accountAdded.id}`)),
      catchError(this.handleError<Account>('addAccount'))
    );
  }

  /** DELETE: delete the Account from the server */
  deleteAccount(account: Account | number): Observable<Account> {
    const id = typeof account === 'number' ? account : account.id;
    const url = `${this.accountsUrl}/${id}`;
    return this.http.delete<Account>(url, httpOptions).pipe(
      tap(_ => this.log(`deleted account id=${id}`)),
      catchError(this.handleError<Account>('deleteAccount'))
    );
  }

  /** DELETE: delete all the Accounts from the server */
  deleteAccounts(): Observable<Account> {
    return this.http.delete<Account>(this.accountsUrl, httpOptions).pipe(
      tap(_ => this.log(`deleted accounts`)),
      catchError(this.handleError<Account>('deleteAccounts'))
    );
  }

  /** PUT: update the Account on the server */
  updateAccount(account: Account, id:number): Observable<Account> {
    return this.http.put<Account>(`${this.accountsUrl}/${id}`, account, httpOptions).pipe(
      // tap(_ => this.log(`updated Account id=${Account.id}`)), // same as the line below
      tap((accountUpdated: Account) => this.log(`updated Account id=${accountUpdated.id}`)),
      catchError(this.handleError<any>('updateAccount'))
    );
  }


    /**
   * Handle Http operation that failed.
   * Let the app continue.
   * @param operation - name of the operation that failed
   * @param result - optional value to return as the observable result
   */
    private handleError<T>(operation = 'operation', result?: T) {
      return (error: any): Observable<T> => {
  
        // TODO: send the error to remote logging infrastructure
        console.error(error); // log to console instead
  
        // TODO: better job of transforming error for user consumption
        this.log(`${operation} failed: ${error.message}`);
  
        // Let the app keep running by returning an empty result.
        return of(result as T);
      };
    }
  
    /** Log a AccountService message with the MessageService */
    private log(message: string) {
      console.log('AccountService: ' + message);
    }

      // for automatic update of number of students in parent component
    public totalItems: BehaviorSubject<number> = new BehaviorSubject<number>(0);
    getCartItems() {
      return this.totalItems.asObservable();
    } 
}
