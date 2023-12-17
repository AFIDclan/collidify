const { Vector2, Collision, Polygon } = require("./index.js")

let vec = new Vector2(1, 2);

console.log(vec.x)
console.log(vec.Magnitude())

let other = new Vector2(3, 4)

let dotted = vec.Dot(other)
let clone = vec.Clone()

console.log(dotted)

console.log(clone.x)
console.log(vec.x)

clone.x = 5

console.log(clone.x)
console.log(vec.x)

// let col = new Collision();

// console.log(col.colPoint1.y)


let poly1 = new Polygon([ new Vector2(0, 0), new Vector2(1, 0), new Vector2(1, 1), new Vector2(0, 1) ]);
let poly2 = new Polygon([ new Vector2(0.1, 0.1), new Vector2(1.1, 0.1), new Vector2(1.1, 1.1), new Vector2(0.1, 1.1) ]);
let col = poly1.CollidesWith(poly2);

console.log(col.collides)
console.log(col.colPoint1.y, col.colPoint1.x)
console.log(col.colPoint2.y, col.colPoint2.x)

poly2.MoveBy(new Vector2(1, 0.1));

col = poly1.CollidesWith(poly2);

console.log(col.collides)
console.log(col.colPoint1.y, col.colPoint1.x)
console.log(col.colPoint2.y, col.colPoint2.x)

let poly3 = new Polygon();

console.log(JSON.stringify(poly1));
