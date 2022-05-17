-- write a SQL query to list the names of all people
-- who have directed a movie that received a rating of at least 9.0

SELECT DISTINCT name
FROM people
WHERE id IN (
    SELECT d.person_id
    FROM directors d
    JOIN ratings r USING(movie_id)
    WHERE r.rating >= 9.0
);