#lang racket

;; ==========================================
;; Statistical Functions
;; ==========================================

;; Mean (average)
(define (calculate-mean lst)
  (if (empty? lst)
      0
      (exact->inexact (/ (apply + lst) (length lst)))))

;; Median
(define (calculate-median lst)
  (if (empty? lst)
      0
      (let* ([sorted-lst (sort lst <)]
             [len (length sorted-lst)]
             [mid (quotient len 2)])
        (if (odd? len)
            (list-ref sorted-lst mid)
            ;; If even, take the exact->inexact average of the two middle elements
            (exact->inexact (/ (+ (list-ref sorted-lst (sub1 mid))
                                  (list-ref sorted-lst mid))
                               2))))))

;; Mode (most frequent element)
;; Note: If there are multiple modes, this returns the first one it finds.
(define (calculate-mode lst)
  (if (empty? lst)
      #f
      (let ([counts (make-hash)])
        ;; Tally the frequencies of each number
        (for ([num lst])
          (hash-update! counts num add1 0))
        
        ;; Find the number with the highest frequency
        (define-values (mode max-count)
          (for/fold ([current-mode #f] [highest-count -1])
                    ([(num count) (in-hash counts)])
            (if (> count highest-count)
                (values num count)
                (values current-mode highest-count))))
        mode)))

;; Min
(define (calculate-min lst)
  (if (empty? lst)
      #f
      (apply min lst)))

;; Max
(define (calculate-max lst)
  (if (empty? lst)
      #f
      (apply max lst)))

;; ==========================================
;; Test Cases and Output
;; ==========================================

(define listA '(3 7 12 5 9 12 4 8 6 12 10 2 14 12 1 11 13 12 15 12 16))
(define listB '(25 18 30 22 25 17 19 25 21 20 18 24 23 25 26 27 18 29 28 25))

(define (display-results list-name lst)
  (printf "Correct results for ~a:\n" list-name)
  (printf "mean = ~a\n" (calculate-mean lst))
  (printf "median = ~a\n" (calculate-median lst))
  (printf "mode = ~a\n" (calculate-mode lst))
  (printf "min = ~a\n" (calculate-min lst))
  (printf "max = ~a\n\n" (calculate-max lst)))

;; Run the tests
(display-results "listA" listA)
(display-results "listB" listB)