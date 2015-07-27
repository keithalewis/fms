# Fundamental Theorem of Asset Pricing - Mathematics

The FTAP places constraints on the dynamics of model prices and cash
flows that are arbitrage free. These constraints lead to a method for
pricing derivative securities *if* they can be replicated by a dynamic
trading strategy. The theory can also be used to measure how poor
the hedge is.

## Outcomes

Let $\Omega$ be the set of all possible outcomes. It can be quite
large. It can include all historical prices and cash flows,
and all potential future prices and cash flows.
Math allows you to think big, even though it might be difficult
to implement on a computer.
<!--
It can also include every newspaper article ever written and
every tweet from twitter, and an encoding of everything that might have
been scrawled on a bathroom wall since ancient Roman times.  Mathematics
allows you to think big even though it might be difficult to implement
on a computer.
-->

## Algebras
A subset of \(\Omega\) is an *event*. An *algebra* on \(\Omega\) is
a collection of events that is closed under complement and union that
also contains the empty set. The algebra also contains \(\Omega\) and
is closed under intersection by De Morgan's laws. This is a perfectly
natural model for events that did not happen, either one of two events
happened, or both events happened. It is a mathematical model faithful
to the everyday meaning of the words 'not', 'and', and 'or'.

A set \(A\in\AA\) is an *atom* if \(B\subseteq A\) and \(B\in\AA\)
implies \(B = A\) or \(B\) is the empty set.
If the cardinality of \(\AA\) is finite, the atoms form
a *partition* of \(\Omega\).
Partitions are the mathematical way of expressing partial
information. We don't know \(\omega\in\Omega\), but we
do know which atom it belongs to.

## Filtrations
A function \(X\colon\Omega\to\RR\) is *measurable* with respect
to \(\AA\) if the set \(\{\omega\in\Omega : X(\omega)\le a\}\) belongs
to \(\AA\) for all \(a\in\RR\). If the cardinality of \(\AA\) is
finite, a function is measurable if and only if it is constant
on atoms. This models a quantity that only depends on the
information available in the algebra.

Let \(T\) be the set of times at which trades can occur. We
assume there is a *total order* on this set denoted by \(<\).
Typically \(T = [0,\infty)\) and represents time in years from
some epoch. In computer implementations this is represented
by a floating point number.

A *filtration* is a collection of algebras indexed by \(T\),
\((\AA_t)_{t\in T}\), such that \(\AA_t\subseteq\AA_u\)
whenever \(t < u\).

## Prices and Cash Flows
The *price* of market instruments at time \(t\) is a
bounded vector-valued function \(X_t\colon\Omega\to\RR^m\)
that is \(\AA_t\)-measurable and \(m\) is the number
of instruments.  We denote this set of
functions by \(B(\Omega,\AA_t,\RR^m)\).

Similarly, a *cash flow* is a function \(C_t\in B(\Omega,\AA_t,\RR^m)\)
that is non-zero at a finite number of times. (We can relax this
constraint to being non-zero at a countably infinite number of
times if \(\inf \{|t - t'| : C_t \not=0{\rm\ and\ }C_{t'}\not=0\} > 0\).)
Stocks pay dividends, bonds pay coupons, in realistic models
there are broker fees and other cash flows that are involved with
the cost of doing business.

## Trades and Positions
A *trading strategy* is a finite number of pairs \((\tau_j,\Gamma_j)\)
where \(\tau_j\in T\) and \(\Gamma_j\in B(\Omega,\AA_{\tau_j},\RR^m)\).
It represents how much is purchased in each market instrument. 

Trades accumulate into a *position* \(\Delta_t = \sum_{\tau_j<t} \Gamma_j\).
Note that any trade at time \(t\) is not counted toward your position.
This reflects the fact that execution is not instantaneous. 

To simplify what follows we define \(\Gamma_t = \Gamma_j\delta_{\tau_j}\) for
\(t\in T\) where
\(\delta_u(t) = 1\) if \(t = u\) and is zero otherwise.

Trading causes numbers to show up in your *account*. At time \(t\),
\(A_t = \Delta_t\cdot C_t - \Gamma_t\cdot X_t\) is the amount
you make: you receive all the cash flows associated with your
position and you pay for the trades you execute. Note \(A_t\)
is zero except when there are cash flows and trades. Even then
it might be zero.

## Value
The (marked-to-market) *value* at time \(t\) is
 \(V_t = (\Gamma_t + \Delta_t)\cdot X_t\). This represents how
much your current trade and position are worth *if* they could
be unwound at the prevailing market price. 
Note that \(\Gamma_t + \Delta_t = \Delta_{t+\epsilon}\) for
small positive \(\epsilon\). If \(\tau_j\le t < \tau_{j+1}\)
then this holds for \(0 < \epsilon < \tau_{j+1} - t\).
It will be your new position when your trade clears.

## Arbitrage
*Arbitrage* exists if there is a trading strategy with
\(\sum_j \Gamma_j = \sum_t \Gamma_t = 0\), \(A_{\tau_0} > 0\), and \(A_t \ge 0\)
for \(t > \tau_0\). In words: arbitrage is a trading
strategy that eventually closes out, makes money on the
first trade, and never loses thereafter.

## Fundamentals
The *fundamental theorem of asset pricing* states that a model is
arbitrage free if and only if there exist
positive, finitely-additive measures
\(\Pi_t\in ba(\Omega,\AA_t)\) such that
\[
	X_t\Pi_t = (\sum_{t<s\le u} C_s\Pi_s + X_u\Pi_u)|_{\AA_t}
\]
for \(t,u\in T\) with \(t < u\). A finitely additive measure
multiplied by a bounded function defines a new finitely additive
measure, so both sides of the equation above are measures. The
sum is a measure in \(ba(\Omega,\AA_u)\) which is then restricted
to the sub-algebra \(\AA_t\). Measures satisfying the above
conditions are called *deflators*.

The *fundamental result of asset pricing* is that in this case
\[
	V_t\Pi_t = (\sum_{t<s\le u} A_s\Pi_s + V_u\Pi_u)|_{\AA_t}
\]
for any trading strategy. Note how the value \(V_t\) acts like the price
\(X_t\) and the account \(A_t\) acts like the cash flow \(C_t\).
Trading strategies allow you to synthesize new instruments.
A derivative security is a contract between two counterparties for
an exchange of cash flows. The contract specifies amounts
\(A_j\) at times \(\tau_j\). We will consider the problem of
finding trading strategies given a contract below.

If \(u\) is the first time after \(t\) for which either \(C_u\) or
\(A_u\) are non-zero, then
\(X_t\Pi_t = (C_u + X_u)\Pi_u|_{\AA_t}\). We now show
\(V_t\Pi_t = (A_u + V_u)\Pi_u|_{\AA_t}\).

\begin{align*}
V_t\Pi_t &= (\Gamma_t + \Delta_t)\cdot X_t\Pi_t\\
	&= (\Gamma_t + \Delta_t)\cdot (C_u + X_u)\Pi_u|_{\AA_t}\\
	&= \Delta_u\cdot (C_u + X_u)\Pi_u|_{\AA_t}\\
	&= (A_u + \Gamma_u\cdot X_u + \Delta_u\cdot X_u)\Pi_u|_{\AA_t}\\
	&= (A_u + (\Gamma_u + \Delta_u)\cdot X_u)\Pi_u|_{\AA_t}\\
	&= (A_u + V_u)\Pi_u|_{\AA_t}\\
\end{align*}

The fundamental result follows by induction on the next times
either either \(C_u\) or \(A_u\) are non-zero.

If a trading strategy closes out (\(\sum_j \Gamma_j = 0\)) then
\[
V_{\tau_0}\Pi_{\tau_0} = \sum_{t > \tau_0} A_t\Pi_t|_{\AA_{\tau_0}}.
\]
If \(A_t \ge0\) for \(t>\tau_0\) then \(V_{\tau_0}\Pi_{\tau_0}\ge0\).
Since \(V_{\tau_0} = \Gamma_0\cdot X_{\tau_0} = -A_{\tau_0}\)
and \(\Pi_{\tau_0}\) is positive, we have \(A_{\tau_0}\le0\).

This proves one direction of the FTAP. We have no
need for the other (much more difficult) direction to show deflators
exist. There are plenty of examples.

## Models

Any martingale can be used to create arbitrage free models.
If \((M_t)_{t\in T}\) is any (vector-valued) martingale
on \(\langle \Omega,P,(\AA_t)_{t\in T}\rangle\)
and \((P_t)_{t\in T}\)is any adapted positive scalar process then
\(X_t = M_tP_t\), \(C_t = 0\)
is an arbitrage free model with deflator
\(\Pi_t = P_t^{-1}P|_{\AA_t}\).
This follows from the definition of a martingale,
\(M_t = E[M_u|\AA_t]\), being equivalent to
\(M_tP|_{\AA_t} = M_uP|_{\AA_t}\) for \(t < u\).

If we want a model having cash flows then
\(X_t = (M_t - \sum_{s\le t} C_sP_s^{-1})P_t\)
fits the bill.

\begin{align*}
&\left(\sum_{t<s\le u}C_s\Pi_s
 + (M_u - \sum_{s\le u}C_sP_s^{-1})P_u\Pi_u\right)|_{\AA_t}\\
&=\sum_{t<s\le u}(C_s\underline{P_s^{-1}P|_{\AA_s}})|_{\AA_t}
 + ((M_u - \sum_{s\le u}C_sP_s^{-1})\underline{P|_{\AA_u}})|_{\AA_t}\\
&= (M_u\underline{P|_{\AA_u})}|_{\AA_t}
 - \sum_{s\le t}(C_sP_s^{-1}P|_{\AA_u})|_{\AA_t}
 + \sum_{t<s\le u} (C_s P_s^{-1}P|_{\AA_s} - C_s P_s^{-1}P|_{\AA_u})|_{\AA_t}\\
&= M_t P|_{\AA_t}
 - \sum_{s\le t}C_sP_s^{-1}P|_{\AA_t}
 + \sum_{t<s\le u} C_s P_s^{-1}P|_{\AA_s}|_{\AA_t}
                 - C_s P_s^{-1}P|_{\AA_s}|_{\AA_t}\\
&= (M_t - \sum_{s\le t}C_sP_s^{-1})P_t\Pi_t\\
\end{align*}
I don't know of any models used for any security that are
an exception to this.

## Hedging
Given a derivative paying \(A_j\) at time \(\tau_j\) how do
we find a hedging strategy \(\Gamma_j\)? *If* it is the case
that \(A_j = \Delta_{\tau_j}\cdot C_{\tau_j} - \Gamma_j\cdot X_{\tau_j}\)
then \(V_{\tau_0} = -A_0 = \Gamma_0\cdot X_{\tau_0}\) so
\(\partial V_{\tau_0}/\partial X_{\tau_0} = \Gamma_0\) and we
have our initial hedge.

At time \(\tau_j\) we have \(V_{\tau_j}
= (\Gamma_j + \Delta_{\tau_j})\cdot X_{\tau_j}\).
Define a function from the Banach space
\(B(\Omega,\AA_{\tau_j},\RR^m)\) to \(B(\Omega,\AA_{\tau_j})\)
by \(X_{\tau_j}\mapsto V_{\tau_j}\). The Fr\'echet derivative
is clearly
\(\partial V_{\tau_j}/\partial X_{\tau_j} = \Gamma_j + \Delta_{\tau_j}\).
This gives the hedge at time \(\tau_j\) since we know \(\Delta_{\tau_j}\)
then.

Note the computation of  \(V_{\tau_j}\) from
\(V_{\tau_j}\Pi_{\tau_j} = \sum_{k > j} A_k\Pi_{\tau_k}|_{\AA_{\tau_j}}\)
only involves the payments specified by the term sheet and the deflators.

The catch is that in general
\(A_j \not= \Delta_{\tau_j}\cdot C_{\tau_j} - \Gamma_j\cdot X_{\tau_j}\).
The difference is the profit-and-loss on the trade.
The classical theory tends to ignore this by assuming markets are
complete. Every trader knows they never are.
This model provides the knobs for measuring how poorly the hedge
might perform. It is closely related to the *gamma profile* of
the trade.

## Canonical Deflator
Fix a probability space and filtration
\(\langle\Omega,P,(\AA_t)_{t\in [0,\infty)}\rangle\).
If at each time \(t\) there is an instrument having price
\(X_t = 1\) and a single cash flow \(R_t\) at time \(t + dt\)
define \(P_t = \prod_{0\le s < t}R_s\) and
\(\Pi_t = P_t^{-1}P|_{\AA_t}\) to be the *canonical deflator*.
These instruments are called the *short realized return*. They
are related to the instantaneous short rate, \(r_t\) by
\(R_t = e^{r_t\,dt}\), but why drag \(e\) into this?

Clearly \(\Pi_t = R_t\Pi_{t+dt}|_{\AA_t}\) so the model is arbitrage free.
In fact \(R_t\Pi_{t+dt}\) is already \(\AA_t\) measurable.
