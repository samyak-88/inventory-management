let products = JSON.parse(localStorage.getItem("products")) || [];

// SAVE
function save() {
    localStorage.setItem("products", JSON.stringify(products));
}

// ADD
function addProduct() {
    let name = document.getElementById("name").value;
    let price = parseFloat(document.getElementById("price").value);
    let qty = parseInt(document.getElementById("qty").value);

    let id = Date.now();

    products.push({ id, name, price, qty });
    save();

    alert("Product added");
}

// RESTOCK
function restock() {
    let id = parseInt(document.getElementById("restockId").value);
    let qty = parseInt(document.getElementById("restockQty").value);

    let p = products.find(p => p.id === id);

    if (p) {
        p.qty += qty;
        save();
        alert("Restocked");
    } else {
        alert("Product not found");
    }
}

// SELL
function sell() {
    let id = parseInt(document.getElementById("sellId").value);
    let qty = parseInt(document.getElementById("sellQty").value);
    let discount = parseFloat(document.getElementById("discount").value) || 0;

    let p = products.find(p => p.id === id);

    if (!p) {
        alert("Not found");
        return;
    }

    if (p.qty < qty) {
        alert("Not enough stock");
        return;
    }

    let total = p.price * qty - discount;
    p.qty -= qty;

    save();
    alert("Sale done. Total: " + total);
}

// DISPLAY
function display() {
    let out = document.getElementById("output");
    out.innerHTML = "";

    products.forEach(p => {
        out.innerHTML += `
            <div>
                ${p.id} | ${p.name} | Qty: ${p.qty} | ₹${p.price}
            </div>
        `;
    });
}

// LOAD ON START
display();
