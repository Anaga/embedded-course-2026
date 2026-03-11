// diagnostics.h
// Lesson 8: Runtime stack and heap monitoring utilities
//
// Use printDiagnostics() in loop() during development to watch for:
//   - Stack high water mark approaching zero (stack overflow risk)
//   - Free heap declining over time (memory leak)
//   - Largest free block much smaller than total free (fragmentation)

#ifndef DIAGNOSTICS_H
#define DIAGNOSTICS_H

#include <Arduino.h>
#include <esp_heap_caps.h>
#include <stdint.h>

// Print a one-line summary of stack and heap state.
// Pass NULL for current task, or a TaskHandle_t for another task.
inline void printDiagnostics(TaskHandle_t task = NULL) {
    UBaseType_t hwm = uxTaskGetStackHighWaterMark(task);
    size_t freeHeap = heap_caps_get_free_size(MALLOC_CAP_DEFAULT);
    size_t maxBlock = heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT);

    Serial.printf("[DIAG] Stack HWM: %4u words | "
                  "Heap free: %6u B | "
                  "Max block: %6u B",
                  (unsigned)hwm,
                  (unsigned)freeHeap,
                  (unsigned)maxBlock);

    // Flag fragmentation: if largest block is much less than total free,
    // the heap is fragmented.
    if (maxBlock < freeHeap / 2) {
        Serial.print("  ** FRAGMENTED **");
    }
    Serial.println();
}

// Print a detailed multi-line report (useful at startup).
inline void printMemoryReport() {
    Serial.println("===== Memory Report =====");
    Serial.printf("  Total free heap : %u bytes\n",
                  (unsigned)heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("  Largest block   : %u bytes\n",
                  (unsigned)heap_caps_get_largest_free_block(MALLOC_CAP_DEFAULT));
    Serial.printf("  Min free ever   : %u bytes\n",
                  (unsigned)heap_caps_get_minimum_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("  Stack HWM       : %u words\n",
                  (unsigned)uxTaskGetStackHighWaterMark(NULL));
    Serial.println("=========================");
}

#endif // DIAGNOSTICS_H
