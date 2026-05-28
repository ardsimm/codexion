#!/bin/bash

PROG="./codexion"
LOG_FILE="/tmp/codexion_test.log"
TIMEOUT=20
PASS=0
FAIL=0
SKIP=0

run_test() {
    local args="$1"
    local desc="$2"

    timeout "$TIMEOUT" $PROG $args > "$LOG_FILE" 2>&1
    local exit_code=$?

    if [ $exit_code -eq 124 ]; then
        echo "  ⏱  TIMEOUT ($TIMEOUT s): $desc"
        ((FAIL++))
    elif grep -q "burned out" "$LOG_FILE"; then
        echo "  ❌ FAIL (burned out): $desc"
        ((FAIL++))
    else
        echo "  ✅ PASS: $desc"
        ((PASS++))
    fi
}

echo "============================================"
echo "         CODEXION TEST SUITE"
echo "============================================"

# ─── HARD ──────────────────────────────────────
echo ""
echo "🔥  [HARD] Burnout edge cases"
echo "--------------------------------------------"
run_test "4 1000 100 300 200 2 400 edf"   "4 philo — hard 25%"
run_test "4 1000 300 100 100 2 200 edf"   "4 philo — hard 35%"
echo "  ⏭  SKIP (argument manquant): 4 400 100 189 110 4 95"
((SKIP++))

# ─── MID ───────────────────────────────────────
echo ""
echo "⚠️   [MID] Devrait passer sans vérif d'optim"
echo "--------------------------------------------"
run_test "4 557 128 222 115 10 150 edf"   "4 philo — 100% vs 12% sur visualizer"
run_test "4 1000 300 100 100 2 199 edf"   "4 philo — mid variant A"
run_test "4 1000 100 300 200 2 399 edf"   "4 philo — mid variant B"

# ─── BASIC ─────────────────────────────────────
echo ""
echo "✅  [BASIC] Tests de base"
echo "--------------------------------------------"
run_test "4 800 200 200 200 5 10 fifo"    "4 philo fifo"
run_test "4 800 200 200 200 5 10 edf"     "4 philo edf"
run_test "10 10000 100 100 100 5 40 fifo" "10 philo fifo"
run_test "20 5000 500 500 10 100 edf"     "20 philo edf"
run_test "5 2000 100 100 100 20 1 fifo"   "5 philo fifo — 20 repas"
run_test "3 10000 2000 2000 2000 2 100 fifo" "3 philo fifo — lents"
run_test "100 10000 66 24 87 10 10 fifo"  "100 philo fifo — masse"

# ─── STARVE / EXIT ─────────────────────────────
echo ""
echo "💀  [STARVE] Doit mourir de faim ou quitter correctement"
echo "--------------------------------------------"
run_test "3 1000 600 10 10 5 100 fifo"    "3 philo — devrait starve"
run_test "1 1000 200 200 200 5 50 fifo"   "1 philo seul"
run_test "5 1000 200 200 200 0 10 fifo"   "5 philo — 0 repas requis"
run_test "2 1 200 200 200 5 10 fifo"      "2 philo — ttd=1 (mort immédiate)"
run_test "2 1000 100 100 100 5 2000 fifo" "2 philo — long délai"

# ─── RÉSUMÉ ────────────────────────────────────
echo ""
echo "============================================"
printf "  ✅ %d passé(s)   ❌ %d échoué(s)   ⏭  %d ignoré(s)\n" $PASS $FAIL $SKIP
echo "============================================"
