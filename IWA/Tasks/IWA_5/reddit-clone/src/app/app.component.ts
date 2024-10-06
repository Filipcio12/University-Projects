import { Component } from '@angular/core';
import { RouterOutlet } from '@angular/router';
import { ArticleComponent } from './article/article.component';
import { Article } from './article/article';
import { NgFor } from '@angular/common';

@Component({
  selector: 'app-root',
  standalone: true,
  imports: [RouterOutlet, ArticleComponent, NgFor],
  templateUrl: './app.component.html',
  styleUrl: './app.component.css'
})
export class AppComponent {
  articles: Article[];

  constructor() {
    this.articles = [
      new Article('Google', 'https://google.com'),
      new Article('Facebook', 'https://facebook.com'),
      new Article('Reddit', 'https://reddit.com'),
    ]
  }

  addArticle(title: HTMLInputElement, link: HTMLInputElement): boolean {
    console.log(`title: ${title.value} and link: ${link.value}`);
    this.articles.push(new Article(title.value, link.value));
    title.value = '';
    link.value = '';
    return false;
  }

  sortedArticles(): Article[] {
    return this.articles.sort((a: Article, b: Article) => b.votes - a.votes);
  }
}
