let isLoggedIn = false;
const ADMIN_USERNAME = "admin";
const ADMIN_PASSWORD = "password123";
let books = [];

function login() {
    const user = document.getElementById("username").value;
    const pass = document.getElementById("password").value;
    if (user === ADMIN_USERNAME && pass === ADMIN_PASSWORD) {
        isLoggedIn = true;
        document.getElementById("login-section").style.display = "none";
        document.getElementById("main-section").style.display = "block";
    } else {
        alert("Invalid credentials!");
    }
}

function addBook() {
    if (!isLoggedIn) return;
    const title = document.getElementById("bookTitle").value.trim();
    const author = document.getElementById("bookAuthor").value.trim();
    if (title && author) {
        books.push({ title, author });
        displayBooks(books);
        document.getElementById("bookTitle").value = "";
        document.getElementById("bookAuthor").value = "";
    }
}

function displayBooks(bookArray) {
    const list = document.getElementById("bookList");
    list.innerHTML = "";
    bookArray.forEach((book, index) => {
        const li = document.createElement("li");
        li.textContent = `${book.title} by ${book.author}`;
        list.appendChild(li);
    });
}

function searchBooks() {
    const term = document.getElementById("searchInput").value.toLowerCase();
    const filtered = books.filter(book => book.title.toLowerCase().includes(term));
    displayBooks(filtered);
}