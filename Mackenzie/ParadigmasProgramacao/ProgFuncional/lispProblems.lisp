(print (car '(1 2 3)))
(print (cdr '(1 2 3)))
(print (cons 0 '(1 2 3)))


(defun soma (lst)
(cond
  ((null lst) 0)
  (t (+ (car lst) (soma (cdr lst))))
  )
)

(print (soma '(1 2 3 4 )))

(defun soma2 (lst1 lst2)
  (cond
    ((null lst1) lst2)
    ((null lst2) lst1)
    (t (cons (+ (car lst1) (car lst2))
             (soma2 (cdr lst1) (cdr lst2))))
    )
  )

(print (soma2 '(1 2 3 ) '(2 3 4 5 )))

(defun menor(lst)
  (men (cdr lst) (car lst)))

(defun men (lst m)
  (cond
    ((null lst) m)
    ((< (car lst) m) (men (cdr lst) (car lst)))
    (t (men(cdr lst) m))
    )
  )

(print(menor '(2 3 4 1 5)))


(defun memp (elt lst)
  (cond
    ((null lst) nil)
    ((eq elt (car lst)) t)
    (t (memp elt (cdr lst)))
    )
  )


(print (memp 5 '(1 2 3 4 5 6)))

(defun deldup (lst)
  (cond
    ((null lst) nil)
    ((memp (car lst) (cdr lst)) (deldup (cdr lst)))
    (t (cons (car lst) (deldup (cdr lst))))
    )
  )

(print (deldup '(1 2 3 4 5 6 1 2 3 4 5 6 1 2 3)))
