-- write a SQL query that lists the names of songs that are by Post Malone

SELECT s.name AS "Post Malone's Songs"
FROM songs s
JOIN artists a
ON s.artist_id = a.id
WHERE a.name = 'Post Malone';