import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import confusion_matrix, accuracy_score, precision_score, recall_score, f1_score, roc_curve, auc

# labels (1 for P, 0 for N)
y_true = np.array([
    1, 1, 0, 0, 1, 1, 0, 0, 1, 1,
    0, 0, 1, 1, 0, 0, 1, 1, 0, 0
])

# Predicted probabilities from Classifier F
y_probs = np.array([
    0.42, 0.18, 0.36, 0.63, 0.15, 0.55, 0.65, 0.75, 0.22, 0.33,
    0.79, 0.44, 0.11, 0.58, 0.51, 0.66, 0.44, 0.77, 0.88, 0.99
])

# -----------------------------
# Q2: Calculate Metrics for Each Threshold
# -----------------------------

thresholds = np.arange(0.0, 1.1, 0.1)

tp_list, fp_list, fn_list, tn_list = [], [], [], []
accuracy_list, precision_list, recall_list, f1_list = [], [], [], []
tpr_list, fpr_list = [], []

# Calculates metrics for each threshold
for t in thresholds:
    y_pred = (y_probs >= t).astype(int)
    
    # Handles cases where confusion_matrix might not return all four values
    cm = confusion_matrix(y_true, y_pred)
    if cm.shape == (2,2):
        tn, fp, fn, tp = cm.ravel()
    else:
        # Adjusts if there are no positives or negatives
        tn = cm[0,0] if cm.shape[0] > 0 and cm.shape[1] > 0 else 0
        fp = cm[0,1] if cm.shape[0] > 0 and cm.shape[1] > 1 else 0
        fn = cm[1,0] if cm.shape[0] > 1 and cm.shape[1] > 0 else 0
        tp = cm[1,1] if cm.shape[0] > 1 and cm.shape[1] > 1 else 0
    
    tp_list.append(tp)
    fp_list.append(fp)
    fn_list.append(fn)
    tn_list.append(tn)
    
    # To handle cases where precision is undefined
    try:
        precision = precision_score(y_true, y_pred)
    except:
        precision = 0.0
    # To handle cases where recall is undefined
    try:
        recall = recall_score(y_true, y_pred)
    except:
        recall = 0.0
    # To handle cases where f1-score is undefined
    try:
        f1 = f1_score(y_true, y_pred)
    except:
        f1 = 0.0
    
    accuracy = accuracy_score(y_true, y_pred)
    
    accuracy_list.append(accuracy)
    precision_list.append(precision)
    recall_list.append(recall)
    f1_list.append(f1)
    
    # Calculate TPR and FPR
    tpr = recall  # TPR is the same as recall
    fpr = fp / (fp + tn) if (fp + tn) != 0 else 0.0
    tpr_list.append(tpr)
    fpr_list.append(fpr)

print(f"{'Threshold':<10} {'TP':<5} {'FP':<5} {'FN':<5} {'TN':<5} {'Accuracy':<10} {'Precision':<10} {'Recall':<10} {'F1-Score':<10} {'TPR':<5} {'FPR':<5}")
print("-" * 80)
for i, t in enumerate(thresholds):
    print(f"{t:<10.1f} {tp_list[i]:<5} {fp_list[i]:<5} {fn_list[i]:<5} {tn_list[i]:<5} "
          f"{accuracy_list[i]:<10.2f} {precision_list[i]:<10.2f} {recall_list[i]:<10.2f} "
          f"{f1_list[i]:<10.2f} {tpr_list[i]:<5.2f} {fpr_list[i]:<5.2f}")


# -----------------------------
# Q3: Generate ROC Curve and Compute AUC
# -----------------------------

# Calculates the ROC curve
fpr, tpr, roc_thresholds = roc_curve(y_true, y_probs)

# Calculates the AUC value
roc_auc = auc(fpr, tpr)

# Plot the ROC curve
plt.figure(figsize=(8,6))
plt.plot(fpr, tpr, color='darkorange', lw=2, label=f'ROC curve (AUC = {roc_auc:.2f})')
plt.plot([0, 1], [0, 1], color='navy', lw=2, linestyle='--', label='Random Guess')
plt.xlim([0.0, 1.0])
plt.ylim([0.0, 1.05])
plt.xlabel('False Positive Rate (FPR)', fontsize=14)
plt.ylabel('True Positive Rate (TPR)', fontsize=14)
plt.title('Receiver Operating Characteristic (ROC) Curve', fontsize=16)
plt.legend(loc="lower right", fontsize=12)
plt.grid(alpha=0.3)
plt.show()

print(f"AUC (Area Under Curve): {roc_auc:.2f}")
