(define (problem bw_5_10)
  (:domain blocks-domain)
  (:objects b1 b2 b3 b4 b5 - block)
  (:init (emptyhand) (on-table b1) (on b2 b3) (on-table b3) (on b4 b2) (on b5 b1) (clear b4) (clear b5)
	(equal b1 b1)
	(equal b2 b2)
	(equal b3 b3)
	(equal b4 b4)
	(equal b5 b5))
  (:goal (and (emptyhand) (on b1 b2) (on-table b2) (on b3 b5) (on-table b4) (on-table b5) (clear b1) (clear b3) (clear b4)))
)
